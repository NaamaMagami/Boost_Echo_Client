//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H

#include <string>
#include <mutex>

using namespace std;

class Book {
public:
    Book() noexcept ;
    Book(const Book &);

    Book(Book &&) noexcept;

    Book(string, string, string);

    Book &operator=(const Book &) = default;

    Book &operator=(Book &&) = default;

    const string &getName() const;

    const string &getpreviousOwner() const;

    const string &getGenere() const;

    const bool &getcurrentlyOnInventory() const;

    void setcurrentlyOnInventory(bool set);

    string setpreviousOwner(string);

    bool empty();

private:
    string name;
    string previousOwner;
    string genere;
    bool currentlyOnInventory;
};


#endif //BOOST_ECHO_CLIENT_BOOK_H
