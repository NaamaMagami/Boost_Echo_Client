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
            string body = words[5];

            if (firstWord=="MESSAGE"){
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
                if (bodyArray[1]=="wish"){
                    string bookName="";
                    for (int k=4;k<body.size();++k){
                        if(bodyArray[k]!=""){
                            bookName=bookName+bodyArray[k];
                        }
                    }
                    Book* myBook=client.containesBook(bookName);
                    if (myBook!= nullptr){
                      string msgToSend="SEND\n"
                                  "destination:"+myBook->getGenere()+"\n\n"+
                                  client.getName()+" has the book "+myBook->getName()+
                                  "\n^@";
                      handler.sendFrameAscii(msgToSend,'\0');
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
                        if (client.wishListContain(myBook)) {
                            string msgToSend = "SEND\n"
                                               "destination:" + myBook->getGenere() + "\n\n" +
                                                " Taking "+myBook->getName()+"from "+bodyArray[1]+
                                               "\n^@";
                            handler.sendFrameAscii(msgToSend, '\0');
                        }
                    }
                    else{

                    }
                }
            }
            else if (firstWord=="RECEIPT"){

            }

        }
    }