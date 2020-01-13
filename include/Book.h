//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H

#include <string>

using namespace std;

class Book {
public:
    Book(string,string,string);

    void changeOwner(string);

    const string &getName() const;

    const string &getpreviousOwner() const;

    const string &getCurrentOwner() const;

    const string &getGenere() const;

    const bool &getcurrentlyOnInventory() const;

    void setcurrentlyOnInventory(bool set);

    string setpreviousOwner(string);

private:
    string name;
    bool currentlyOnInventory;
    string previousOwner;
    string genere;

};


#endif //BOOST_ECHO_CLIENT_BOOK_H
