//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H

#include <string>

using namespace std;

class Book {
public:
    Book(string,string);
private:
    string name;
    string borrowedFrom;
};


#endif //BOOST_ECHO_CLIENT_BOOK_H
