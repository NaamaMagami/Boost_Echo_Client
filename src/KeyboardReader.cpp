

#include "KeyboardReader.h"
//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//
#include <iostream>
#include <connectionHandler.h>
#include "Client.h"
using namespace std;
using boost::asio::ip::tcp;

KeyboardReader::KeyboardReader(ConnectionHandler& _handler, Client _client): handler(_handler),client(_client),subId(0){
}

void KeyboardReader::run(){
    bool loggedIn=true;
    while (loggedIn) {
        if(handler.getIsClosed()){
            loggedIn=false;
        }
        else{
            const short bufsize = 1024;
            char buf[bufsize];
            cin.getline(buf, bufsize);
            string line(buf);
            int len = line.length();
            string command[len];
            int i = 0;
            string msgToSend;
            //extracting the input line to array called "command"-->>>could be done with BOOST
            for (char c:line) {
                if (c != ' ') {
                    command[i] = command[i] + c;
                } else {
                    i = i + 1;
                }
            }
            if (command[0] == "login") {
                msgToSend = "CONNECT\n"
                            "accept-version:1.2\n"
                            "host:stomp.cs.bgu.ac.il\n"
                            "login:" + command[2] + "\n"
                                                    "passcode:" + command[3] + "\n"
                                                                               "\n^@";
                handler.sendLine(msgToSend);
            }
            //add to the map "join genere"
            if (command[0] == "join") {
                string stringSubId = to_string(subId);
                int thisR = client.getReceiptNum();
                msgToSend = "SUBSCRIBE\n"
                            "destination:" + command[1] + "\n"
                                                          "id:" + stringSubId + "\n"
                                                                                "receipt:" + to_string(thisR) + "\n"
                                                                                                                "\n^@";
                subId = subId + 1;
                client.addMessage(thisR, "join " + command[1]);
                handler.sendLine(msgToSend);

            }
            //find out what to do with the receipt number
            if (command[0] == "exit") {
                string stringSubId = to_string(subId);
                int thisR = client.getReceiptNum();
                msgToSend = "UNSUBSCRIBE\n"
                            "destination:" + command[1] + "\n" +
                            "id:" + stringSubId + "\n" +
                            "receipt:" + to_string(thisR) + "\n"
                                                            "\n^@";
                client.addMessage(thisR, "exit " + command[1]);
                handler.sendLine(msgToSend);

            }
            if (command[0] == "add") {
                msgToSend = "SEND\n"
                            "destination:" + command[1] + "\n"
                                                          "\n" +
                            client.getName() + " has added the book " + command[2] + "\n"
                                                                                     "\n^@";
                Book *bookToAdd = new Book(command[2], client.getName(), command[1]);
                client.addBook(command[1], bookToAdd);
                handler.sendLine(msgToSend);
            }
            if (command[0] == "borrow") {
                string gen = command[1];
                string bookName = command[2];
                msgToSend = "SEND\n"
                            "destination:" + gen + "\n"
                                                   "\n" +
                            client.getName() + " wish to borrow " + bookName + "\n"
                                                                               "\n^@";
                Book *bookToAdd = new Book(command[2], client.getName(), command[1]);
                client.addToWishList(bookToAdd);
                handler.sendLine(msgToSend);
            }
            if (command[0] == "return") {
                string gen = command[1];
                string bookName = command[2];
                Book *bookToReturn = client.getFromBooksByGenere(gen, bookName);
                msgToSend = "SEND\n"
                            "destination:" + gen + "\n"
                                                   "\n" +
                            " Returning " + bookName + " to " + bookToReturn->getpreviousOwner() + "\n"
                                                                                                   "\n^@";
                handler.sendLine(msgToSend);
                client.removeBook(gen, bookToReturn);
            }
            if (command[0] == "status") {
                string gen = command[1];
                msgToSend = "SEND\n"
                            "destination:" + gen + "\n"
                                                   "\n" +
                            "book status" + "\n^@";
                handler.sendLine(msgToSend);
            }

            if (command[0] == "logout") {
                int thisR = client.getReceiptNum();
                msgToSend = "DISCONNECT\n"
                            "receipt:" + to_string(thisR) + "\n\n^@";
                client.addMessage(thisR, "logout");
                handler.sendLine(msgToSend);
            }




//        if (!connectionHandler.sendLine(line)) {
//            std::cout << "Disconnected. Exiting...\n" << std::endl;
//            break;
//        }
//        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
//        std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
//
//
//        // We can use one of three options to read data from the server:
//        // 1. Read a fixed number of characters
//        // 2. Read a line (up to the newline character using the getline() buffered reader
//        // 3. Read up to the null character
//        std::string answer;
//        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
//        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
//        if (!connectionHandler.getLine(answer)) {
//            std::cout << "Disconnected. Exiting...\n" << std::endl;
//            break;
//        }
//
//        len=answer.length();
//        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
//        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
//        answer.resize(len-1);
//        std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
//        if (answer == "bye") {
//            std::cout << "Exiting...\n" << std::endl;
//            break;
//        }
        }
    }}


