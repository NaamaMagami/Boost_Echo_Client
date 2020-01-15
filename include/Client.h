//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENT_H
#define BOOST_ECHO_CLIENT_CLIENT_H

#include "Book.h"
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;


class Client {
private:
    string name;
    string passcode;
    vector<Book*>* wishList;
    unordered_map<string,vector<Book*>*>* booksByGenere;
    vector<string>* subs;
    int receiptNum=0;
    unordered_map<int,string>* messsageByReceipt;

public:


    Client();

    Client(string _name, string _passcode);

    string getByFirstKey(int first);
    void addMessage(int,string);
    void addBook(string,Book*);
    void removeBook(string,Book*);
    int getReceiptNum();

    const string &getName() const;

    void addToWishList(Book *book);

    Book *getFromBooksByGenere(string gen, string bookName);

    Book* containesBook(string bookName);

    Book *containedBeforeBook(string bookName);

    bool wishListContain(string name);

    string getInventory(string);

    void addToSubs(string topic);

    void removeFromSubs(string topic);

    string getReceipt(int num);

    void clearClient();
    void printMap();




};


#endif //BOOST_ECHO_CLIENT_CLIENT_H
