//
// Created by naama on 14/01/2020.
//
#include <iostream>
#include <boost/asio/ip/tcp.hpp>
#include <Client.h>
#include <readFromServ.h>
#include <thread>
#include "StompBookClubClient.h"
#include "connectionHandler.cpp"

using namespace std;
using boost::asio::ip::tcp;

int main (int argc, char *argv[]) {
    bool wasThereAConnection = false;

    while (!wasThereAConnection) {
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
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
        if (command[0] == "login") {
            string hostAndPort = command[1];
            string userName = command[2];
            string passcode = command[3];
            string myHost = boost::asio::ip::host_name();

            string serverHost="";
            string serverPort="";
            int j=0;
            for (char c:hostAndPort) {
                if (c != ':') {
                    serverHost=serverHost+c;
                    j=j+1;
                } else {
                    serverPort=hostAndPort.substr(j,hostAndPort.size());
                    break;
                }
            }
            short port = stoi(serverPort);

            msgToSend = "CONNECT\n"
                        "accept-version:1.2\n"
                        "host:"+myHost+"\n"
                                       "login:" + userName + "\n"
                                                             "passcode:" + passcode + "\n""\n^@";

            ConnectionHandler* handler= new ConnectionHandler(serverHost,port);
            handler->sendLine(msgToSend);
            Client* client = new Client(userName,passcode);
            readFromServ* socketReader = new readFromServ(*handler,*client);

            thread socketThread (&readFromServ::run,socketReader);

            wasThereAConnection=true;
        }
    }
}
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

}
}
}