

#include "KeyboardReader.h"
//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//
#include <iostream>
#include <connectionHandler.h>
#include "Client.h"
using namespace std;
using boost::asio::ip::tcp;

KeyboardReader::KeyboardReader(ConnectionHandler& _handler): handler(_handler),subId(0),receiptNum(0){}

void KeyboardReader::run(){
    bool loggedIn=true;
    while (loggedIn) {

        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);
        int len=line.length();
        string command [len];
        int i = 0;
        string msgToSend;
        //extracting the input line to array called "command"-->>>could be done with BOOST
        for (char c:line) {
            if (c!=' ') {
                command[i] = command[i] + c;
            } else {
                i = i + 1;
            }
        }
        if (command[0]=="login"){
            msgToSend="CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:"+command[2]+"\npasscode:"+command[3]+"\n\n^@";
        }
        if (command[0]=="join"){
            string stringSubId=to_string(subId);
            msgToSend="SUBSCRIBE\ndestination:"+command[1]+"\nid:"+stringSubId+"\nreceipt:"+to_string(receiptNum)+"\n\n^@";
            subId=subId+1;
            receiptNum=+1;
        }
        if(command[0]=="add"){
            msgToSend="SEND\ndestination:"+command[1]+"\n\n

        }
        if (!connectionHandler.sendLine(line)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        std::cout << "Sent " << len+1 << " bytes to server" << std::endl;


        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        std::string answer;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!connectionHandler.getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }

        len=answer.length();
        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        answer.resize(len-1);
        std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
        if (answer == "bye") {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
    }
}
