//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENT_H
#define BOOST_ECHO_CLIENT_CLIENT_H

#include "Book.h"

using namespace std;


class Client {
public:
    Client(string name, string passcode);
    void addMessage(int,string);
    void addBook(string,Book*);
//    void subscribe(string);
//    void unSubscribe(string);
private:
    string name;
    string passcode;
    map<string,vector<Book*>*>booksByGenere;
//    vector<string> subs;
    int receiptNum;
    map<int,string>messsageByReceipt;
};


#endif //BOOST_ECHO_CLIENT_CLIENT_H
