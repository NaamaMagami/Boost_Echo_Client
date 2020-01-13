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

    Client();

    void addMessage(int,string);
    void addBook(string,Book*);
    void removeBook(string,Book*);
    int getReceiptNum();

    const string &getName() const;

//    void subscribe(string);
//    void unSubscribe(string);
    void addToWishList(Book *book);

    Book *getFromBooksByGenere(string gen, string bookName);

    Book* containesBook(string bookName);

    Book *containedBeforeBook(string bookName);

    bool wishListContain(string name);

    string getInventory(string);

private:
    string name;
    string passcode;
    vector<Book*>* wishList;
    map<string,vector<Book*>*>booksByGenere;
//    vector<string> subs;
    int receiptNum;
    map<int,string>messsageByReceipt;

};


#endif //BOOST_ECHO_CLIENT_CLIENT_H
