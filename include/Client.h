//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENT_H
#define BOOST_ECHO_CLIENT_CLIENT_H
using namespace std;


class Client {
public:
    Client(string name, string passcode);

private:
    string name;
    string passcode;


};


#endif //BOOST_ECHO_CLIENT_CLIENT_H
