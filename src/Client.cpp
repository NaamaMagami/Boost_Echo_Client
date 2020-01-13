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
    booksByGenere.at(topic)->push_back(book);
}


void Client::removeBook(string genere,Book * book) {
    vector<Book*>::iterator iter;
    if (booksByGenere.at(genere)!= nullptr){
        for (iter = booksByGenere.at(genere)->begin() ; iter <booksByGenere.at(genere)->end();iter++){
            if (*iter == book)
                booksByGenere.at(genere)->erase(iter);
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



    void Client::delFromBooksByGenere(Book* book){
        vector<Book*>::iterator iter;
        for (iter = booksByGenere.at(book->getGenere())->begin() ; iter <booksByGenere.at(book->getGenere())->end();iter++){
            if(iter.getName()==book->getName())
                booksByGenere.at(book->getGenere())->erase(iter);
        }

    }

bool Client::wishListContain(Book * book) {
    for(Book* b:*wishList){
        if(b->getName()==book->getName())
            return true;
    }
    return false;
}
    void Client::addToWishList(Book* book){
    wishList->push_back(book);
    }

//void Client::subscribe(string genere) {
//    subs.push_back(genere);
//}
//
//void Client::unSubscribe(string genere) {
//    for (int i=0; i<subs.size();++i){
//        if (subs.at(i)==genere)
//            subs.erase(i);
//    }
//}

