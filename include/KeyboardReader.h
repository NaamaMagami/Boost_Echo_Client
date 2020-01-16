//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDREADER_H
#define BOOST_ECHO_CLIENT_KEYBOARDREADER_H


#include "connectionHandler.h"
#include "Client.h"

class KeyboardReader {
public:
//    KeyboardReader(ConnectionHandler& _handler);

    KeyboardReader(ConnectionHandler &_handler, Client _client);

    void run();
    void close();
private:
    ConnectionHandler& handler;
    int subId;
    Client client;
    bool loggedIn;

};


#endif //BOOST_ECHO_CLIENT_KEYBOARDREADER_H
