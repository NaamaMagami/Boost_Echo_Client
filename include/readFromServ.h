//
// Created by magami@wincs.cs.bgu.ac.il on 13/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_READFROMSERV_H
#define BOOST_ECHO_CLIENT_READFROMSERV_H


#include "connectionHandler.h"

class readFromServ {
public:
    readFromServ(ConnectionHandler &,Client& );
    void run();
private:
    ConnectionHandler &handler ;



};


#endif //BOOST_ECHO_CLIENT_READFROMSERV_H
