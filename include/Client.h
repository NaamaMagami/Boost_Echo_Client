//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENT_H
#define BOOST_ECHO_CLIENT_CLIENT_H

#include "Book.h"
#include <vector>
#include <map>
#include <unordered_map>
#include <mutex>

using namespace std;


class Client {
private:
    Book emptyBook;
    string name;
    string passcode;
    vector<Book>* wishList;
    unordered_map<string,vector<Book>>* booksByGenere;
    vector<string>* subs;
    int receiptNum=0;
    unordered_map<int,string>* messsageByReceipt;
    unordered_map<string ,string>* topicsAndSubsId;
    //mutex locki;

public:
    void clearMe();
    //~Client();
    Client(string _name, string _passcode);
    string getByFirstKey(int first);
    void addMessage(int,string);
    void addBook(string,Book);
    void removeBook(const string&,Book&);
    int getReceiptNum();
    string fixName(string);

    const string &getName() const;

    void addToWishList(Book& p_book);

    Book &getFromBooksByGenere(const string& gen, string bookName);

    Book& containesBook(string bookName);

    Book &containedBeforeBook(const string& bookName);

    bool wishListContain(const string& p_name);

    string getInventory(const string&);

    void addToSubs(const string& topic);

    void removeFromSubs(string topic);

    string getReceipt(int num);

    //void clearClient();
    //void printMap();
    void addTotopicsAndSubsId(const string&,string);
    string getSubIdByTopic(string);

    void removeFromTopicsAndSubsId(const string&);
    void printInventory();

    void removeFromWishList(string p_name);

};


#endif //BOOST_ECHO_CLIENT_CLIENT_H
