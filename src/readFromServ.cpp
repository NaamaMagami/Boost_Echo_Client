//
// Created by magami@wincs.cs.bgu.ac.il on 13/01/2020.
//
//#include <boost/algorithm/string.hpp>dc++.h>
#include <boost/algorithm/string.hpp>
#include <Client.h>
#include "readFromServ.h"
#include "connectionHandler.h"

#include <array>
using namespace std;

readFromServ::readFromServ(ConnectionHandler& _handler1,Client& _client):handler(_handler1),client(_client){}


void readFromServ::run() {
    bool connected=true;
    while (connected) {
        string command="";
        handler.getFrameAscii(command,'\0');

        string words[command.size()];
        int i=0;
        for (char c:command) {
            if (c!='\n') {
                words[i] = words[i] + c;
            } else {
                i = i + 1;
            }
        }
        string firstWord=words[0];


        if (firstWord=="MESSAGE"){
            string body = words[5];
            string topic=words[3].substr(12,words[3].size());
            string toPrint=topic+":"+body;
            cout<<toPrint<<endl;
            string bodyArray[body.size()];
            for (int i=0; i<bodyArray->size();++i){
                bodyArray[i]="";
            }
            int j=0;
            for (char c:body) {
                if (c=='\n'){
                    break;
                }
                if (c!=' ') {
                    bodyArray[j] = bodyArray[j] + c;
                } else {
                    j = j + 1;
                }
            }
            if (bodyArray[1]=="wish") {
                string bookName = "";
                for (int k = 4; k < body.size(); ++k) {
                    if (bodyArray[k] != "") {
                        bookName = bookName + bodyArray[k];

                    }
                    Book *myBook = client.containesBook(bookName);
                    if (myBook != nullptr) {
                        string msgToSend = "SEND\n"
                                           "destination:" + myBook->getGenere() + "\n\n" +
                                           client.getName() + " has the book " + myBook->getName() +
                                           "\n^@";
                        handler.sendFrameAscii(msgToSend, '\0');
                    }
                }
            }
            else if(bodyArray[1]=="has"&&bodyArray[2]!="added"){
                string bookName="";
                for (int k=2;k<body.size();++k){
                    if(bodyArray[k]!=""){
                        bookName=bookName+bodyArray[k];
                    }
                }
                Book* myBook=client.containesBook(bookName);
                if (myBook == nullptr) {
                    if (client.wishListContain(bookName)) {
                        string msgToSend = "SEND\n"
                                           "destination:" + topic + "\n\n" +
                                           " Taking "+myBook->getName()+" from "+bodyArray[0]+
                                           "\n^@";
                        Book* myOldBook=client.containedBeforeBook(bookName);
                        if(myOldBook!= nullptr){
                            myOldBook->setcurrentlyOnInventory(true);
                            myOldBook->setpreviousOwner(bodyArray[0]);
                        }
                        else {
                            Book* myNewBook=new Book(bookName,bodyArray[0],topic);
                            client.addBook(topic,myNewBook);
                        }
                        handler.sendFrameAscii(msgToSend, '\0');
                    }
                }
            }
            else if(bodyArray[0]=="Taking" & bodyArray[bodyArray->size()-1]==client.getName()){
                string bookName="";
                int k=1;
                while (bodyArray[k]!="from"){
                    bookName=bookName+bodyArray[k];
                    ++k;
                }
                if (client.containesBook(bookName)!= nullptr) {
                    client.removeBook(topic, client.containesBook(bookName));
                }
                else{
                    cout<<"ERROR: CLIENT GAVE A BOOK BUT DOES NOT OWN IT!";
                }
            }
            else if(bodyArray[0]=="Returning"){
                int k=1;
                string bookToReturn ="";
                while (bodyArray[k]!="to"){
                    bookToReturn=bookToReturn+bodyArray[k];
                    ++k;
                }
                if (bodyArray[bodyArray->size()]==client.getName()){
                    if (client.containedBeforeBook(bookToReturn)!= nullptr) {
                        client.addBook(topic, client.containesBook(bookToReturn));
                    }
                    else{
                        cout<<"ERROR: CLIENT GAVE A BOOK BUT DOES NOT HAVE IT ON CONAIED BEFORE!";
                    }
                }
            }
            else if(bodyArray[0]=="book"){
                string msgToSend = "SEND\n"
                                   "destination:" +topic+ "\n\n" +
                                   client.getInventory(topic)+
                                   "\n^@";
            }
        }

        else if (firstWord=="RECEIPT"){
            string receiptId=words[1].substr(11,words[1].size());
            cout<<receiptId<<endl;
            string action=client.getReceipt(stoi(receiptId));
            string recieptArray[action.size()];
            int j=0;
            for (char c:action) {
                if (c=='\n'){
                    break;
                }
                if (c!=' ') {
                    recieptArray[j] = recieptArray[j] + c;
                } else {
                    j = j + 1;
                }
            }
            string first=recieptArray[0];

            if (first=="join"){
                client.addToSubs(recieptArray[1]);
                cout<<"Joined club "+recieptArray[1]<<endl;
            }
            else if (first=="logout"){
                client.clearClient();
                handler.close();
                connected= false;
            }
            else if ("exit"){
                client.removeFromSubs(recieptArray[1]);
                cout<<"Exited club "+recieptArray[1]<<endl;

            }
        }

    }
}