//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//
#include <iostream>
#include <connectionHandler.h>
#include "Client.h"
#include <vector>
using namespace std;

Client::Client(string _name,string _passcode): name(_name), passcode(_passcode){
    map<string,vector<Book*>> booksByGenere;
    receiptNum=0;
    map<int,string>messsageByReceipt;
    wishList = new vector<Book*>;
    vector<string> subs;
}

void Client::addToSubs(string topic){
    subs.push_back(topic);
}

void Client::removeFromSubs(string topic){
    vector<string>::iterator iter ;
    for (iter=subs.begin();iter<subs.end();++iter){
        if ((*iter)==topic){
            subs.erase(iter);
        }
    }
}
string Client::getReceipt(int num){
    return messsageByReceipt.at(num);
}
const string &Client::getName() const {
    return name;
}

void Client::addMessage(int receipt, string message) {
    messsageByReceipt.insert(make_pair(receipt,message));
}

int Client::getReceiptNum(){
    receiptNum+=1;
    return receiptNum;
}

Client::Client() {}

void Client::addBook(string topic, Book * book) {
    if (booksByGenere.at(topic) == nullptr){
        booksByGenere.insert(make_pair(topic,new vector<Book*>));
    }
    if(containedBeforeBook(book->getName()))
        book->setcurrentlyOnInventory(true);
    else {
        booksByGenere.at(topic)->push_back(book);
    }
}
Book* Client::containesBook(string bookName) {
        for (map<string, vector<Book*>*>::const_iterator it = booksByGenere.begin(); it != booksByGenere.end(); ++it){
            for (Book* book : *it->second){
                if (book->getName()==bookName & book->getcurrentlyOnInventory()){
                    return book;
                }
            }
        }
        return nullptr;

}

string Client:: getInventory(string topic) {
    string temp="";
    for  (Book* book : *(booksByGenere.at(topic))){
        temp=temp+","+book->getName();
    }
    return temp;
}

Book* Client::containedBeforeBook(string bookName) {
    for (map<string, vector<Book*>*>::const_iterator it = booksByGenere.begin(); it != booksByGenere.end(); ++it){
        for (Book* book : *it->second){
            if (book->getName()==bookName & !book->getcurrentlyOnInventory()){
                return book;
            }
        }
    }
    return nullptr;

}


void Client::removeBook(string genere,Book * book) {
    vector<Book*>::iterator iter;
    if (booksByGenere.at(genere)!= nullptr){
        for (iter = booksByGenere.at(genere)->begin() ; iter <booksByGenere.at(genere)->end();++iter){
            if ((*iter)->getName() == book->getName())
                (*iter)->setcurrentlyOnInventory(false);
        }
    }
}

Book* Client::getFromBooksByGenere(string gen,string bookName){

    if(booksByGenere.at(gen)== nullptr)
        return nullptr;
    for(Book* b: *booksByGenere.at(gen)){
        if(b->getName()==bookName)
            return b;
    }
}

bool Client::wishListContain(string name) {
    for(Book* b:*wishList){
        if(b->getName()==name)
            return true;
    }
    return false;
}
    void Client::addToWishList(Book* book){
    wishList->push_back(book);
    }


