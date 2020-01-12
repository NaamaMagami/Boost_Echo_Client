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
private:
    string name;
    string originalOwner;
    string currentOwner;
    string genere;
};


#endif //BOOST_ECHO_CLIENT_BOOK_H
