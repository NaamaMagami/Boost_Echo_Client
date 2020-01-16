

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
    loggedIn=true;
}

void KeyboardReader::run(){

    while (loggedIn) {
            const short bufsize = 1024;
            char buf[bufsize];
            try {
                cin.getline(buf, bufsize);
            }catch(exception){
                cout<<"logged out"<<endl;
            }
            string line(buf);
            int len = line.length();
            string command[len];
            int i = 0;
            string msgToSend;
            for (char c:line) {
                if (c != ' ') {
                    command[i] = command[i] + c;
                } else {
                    i = i + 1;
                }
            }

            if (command[0] == "join") {
                string stringSubId = to_string(subId);
                int thisR = client.getReceiptNum();
                msgToSend = "SUBSCRIBE\n"
                            "destination:" + command[1] + "\n"
                                                          "id:" + stringSubId + "\n"
                                                                                "receipt:" + to_string(thisR) + "\n";
                client.addTotopicsAndSubsId(command[1],stringSubId);
                subId = subId + 1;
                client.addMessage(thisR, "join " + command[1]);
                handler.sendLine(msgToSend);
            }
            //find out what to do with the receipt number
            if (command[0] == "exit") {

                string stringSubId = client.getSubIdByTopic(command[1]);
                int thisR = client.getReceiptNum();
                msgToSend = "UNSUBSCRIBE\n"
                            "id:" + stringSubId + "\n" +
                            "receipt:" + to_string(thisR) + "\n"
                                                            "\n";

                client.addMessage(thisR, "exit " + command[1]);
                handler.sendLine(msgToSend);
                client.removeFromTopicsAndSubsId(command[1]);
            }
            if (command[0] == "add") {
                string bookName="";
                int i=2;
                while (command[i].compare("")!=0) {
                    bookName=bookName+string(command[i])+" ";
                    i=i+1;
                }
                int j=0;
                int k=bookName.length();
                for (int i=0; i<bookName.length();++i){
                    if (bookName.at(j)==' '& bookName.at(j+1)==' '){
                        k=j;
                        break;
                    }
                }
                bookName=client.fixName(bookName);

                cout<<"adding the book "+bookName<<endl;
                msgToSend = "SEND\n"
                            "destination:" + command[1] + "\n"
                                                          "\n"+
                            client.getName() + " has added the book " + bookName + "\n"
                                                                                     "\n";


                Book *bookToAdd = new Book(bookName, client.getName(), command[1]);
                client.addBook(command[1], bookToAdd);
                handler.sendLine(msgToSend);
            }
            if (command[0] == "borrow") {
                string gen = command[1];
                string bookName="";

                for (int i=2;i<command->length();++i) {
                    if(command[i]!=" ")
                        bookName=bookName+" "+command[i];
                }
               bookName=client.fixName(bookName);

                msgToSend = "SEND\n"
                            "destination:" + gen + "\n"
                                                   "\n" +
                            client.getName() + " wish to borrow "+bookName + "\n"
                                                                              "\n";
              ;
                Book *bookToAdd = new Book(bookName, client.getName(), command[1]);
                client.addToWishList(bookToAdd);
                handler.sendLine(msgToSend);
            }
            if (command[0] == "return") {
                string gen = command[1];
                string bookName="";
                for (int i=2;i<command->length();++i) {
                    if(command[i]!=" ")
                        bookName=bookName+command[i]+" ";
                }

                int j=0;
                int k=bookName.length();
                for (int i=0; i<bookName.length();++i){
                    if (bookName.at(j)==' '& bookName.at(j+1)==' '){
                        k=j;
                        break;
                    }
                }
                bookName=client.fixName(bookName);
                cout<<"returning book:"+bookName<<endl;
                cout<<"from gen:"+gen<<endl;
                Book *bookToReturn = client.getFromBooksByGenere(gen, bookName);

                msgToSend = "SEND\n"
                            "destination:" + gen + "\n"
                                                   "\n" +
                            "Returning " + bookName + " to " + bookToReturn->getpreviousOwner() + "\n"
                                                                                                   "\n";
                handler.sendLine(msgToSend);
                client.removeBook(gen, bookToReturn);
            }
            if (command[0] == "status") {
                string gen = command[1];
                msgToSend = "SEND\n"
                            "destination:" + gen + "\n"
                                                   "\n" +
                            "book status" + "\n\n";
                handler.sendLine(msgToSend);
            }

            if (command[0] == "logout") {
                int thisR = client.getReceiptNum();
                msgToSend = "DISCONNECT\n"
                            "receipt:" + to_string(thisR) + "\n\n";
                client.addMessage(thisR, "logout");
                handler.sendLine(msgToSend);
                loggedIn=false;
                break;
            }
//login 132.72.45.155:7777 left 12

        }
    cout<< "finished while"<<endl;
    }


