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
    vector<string> subs;
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

