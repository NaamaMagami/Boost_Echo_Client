    //
    // Created by magami@wincs.cs.bgu.ac.il on 13/01/2020.
    //
#include <boost/algorithm/string.hpp>dc++.h>
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

            vector<string> words;
            boost::split(words,command," ");
            string
            if (words[0]=="MESSAGE"){

            }
            if (words[0]=="RECEIPT"){

            }

        }
    }