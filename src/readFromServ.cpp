    //
    // Created by magami@wincs.cs.bgu.ac.il on 13/01/2020.
    //
//#include <boost/algorithm/string.hpp>dc++.h>
#include <boost/algorithm/string.hpp>
#include <Client.h>
#include "readFromServ.h"
    #include "connectionHandler.h"
    using namespace std;

    readFromServ::readFromServ(ConnectionHandler& _handler1,Client& _client):handler(_handler1){}


    void readFromServ::run() {

        bool connected=true;
        while (connected) {
            string command="";
            handler.getLine(command);

            string message = "message\nsubscription:78\nMessage-id:00021\ndestination:sci-fi\n\nBob wish to borrow Dune\n^@";
            string words[message.size()];
            int i=0;
            for (char c:message) {
                if (c!='\n') {
                    words[i] = words[i] + c;
                } else {
                    i = i + 1;
                }
            }
            string firstWord=words[0];
            string body = words[5];

            if (firstWord=="MESSAGE"){
                string bodyArray[body.size()];
                int j=0;
                for (char c:message) {
                    if (c!=' ') {
                        bodyArray[j] = bodyArray[j] + c;
                    } else {
                        j = j + 1;
                    }
                }
                if (bodyArray[1]=="wish"){

                }
                else if(bodyArray[1]=="has"&&bodyArray[2]!="added"){

                }
            }
            else if (firstWord=="RECEIPT"){

            }

        }
    }