//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDREADER_H
#define BOOST_ECHO_CLIENT_KEYBOARDREADER_H


#include "connectionHandler.h"

class KeyboardReader {
    public:
    KeyboardReader(ConnectionHandler& _handler);
    void connect();

    private:
    ConnectionHandler& handler;

};


#endif //BOOST_ECHO_CLIENT_KEYBOARDREADER_H
