//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//
#include <iostream>
#include <connectionHandler.h>
#include "Client.h"
#include "_T1.h"
#include <vector>
#include <type_traits>
#include <unordered_map>



using namespace std;

Client::Client(string _name, string _passcode): name(_name), passcode(_passcode) {
    wishList = new vector<Book *>;
    booksByGenere = new unordered_map<string, vector<Book *> *>;
    subs = new vector<string>;
    messsageByReceipt = new unordered_map<int, string>;
    topicsAndSubsId = new unordered_map<string, string>;
}

void Client::addToSubs(string topic){
    subs->push_back(topic);
    vector<Book*>* vec=new vector<Book*>;
    booksByGenere->insert(make_pair(topic,vec));
}
void Client::addTotopicsAndSubsId(string topic,string subId){
    topicsAndSubsId->insert(make_pair(topic,subId));
}

void Client::removeFromTopicsAndSubsId(string topic){
    topicsAndSubsId->erase(topic);
}

string Client::getSubIdByTopic(string topic){
    string result;
    for(pair<string,string> mapPair: *topicsAndSubsId){
        if(mapPair.first==topic)
            return mapPair.second;
    }
    return nullptr;
}

void Client::removeFromSubs(string topic){
    vector<string>::iterator iter ;
    for (iter=subs->begin();iter<subs->end();++iter){
        if ((*iter)==topic){
            subs->erase(iter);
        }
    }
}

string Client::getByFirstKey(int first){
    for(pair<int,string> mapPair: *messsageByReceipt){
        if(mapPair.first==first)
            return mapPair.second;
    }
    return nullptr;

}
string Client::getReceipt(int num){
    string output=getByFirstKey(num);
    return output;
}
const string &Client::getName() const {
    return name;
}

void Client::addMessage(int receipt, string message) {
    messsageByReceipt->insert(pair<int,string>(receipt,message));
}
void Client::printMap(){
    for(pair<int,string> mapPair:*messsageByReceipt){
        cout<<to_string(mapPair.first)+" , "+mapPair.second<<endl;

    }
}

int Client::getReceiptNum(){
    receiptNum+=1;
    return receiptNum;
}

Client::Client() {}

void Client::addBook(string topic, Book * book) {
    if (booksByGenere->count(topic) == 0){
        booksByGenere->insert(make_pair(topic,new vector<Book*>));
    }
    if(containedBeforeBook(book->getName()))
        book->setcurrentlyOnInventory(true);
    else {
        booksByGenere->at(topic)->push_back(book);
    }
}
string Client::fixName(string oldName)  {
    std::string newName=oldName;
    bool first=false;
    bool last=false;
    int count;
    int i=0;
    char curr;
    while(!first& i<newName.length()) {
        curr=newName.at(i);
        if (curr!=' ') {

            newName = newName.substr(i, newName.length());
            first = true;
        }
        i=i+1;
    }
    i= newName.length()-1;
    while(i>=0 & !last){
        curr=newName.at(i);
        if(curr!=' '){
            newName=newName.substr(0,i+1);
            last=true;
        }
        i=i-1;
    }
    return newName;
}



Book* Client::containesBook(string bookName) {
    cout<<"----in containesBook---"<<endl;
    cout<<bookName<<endl;
    cout<<"----in containesBook---"<<endl;
    for (auto it = booksByGenere->begin(); it != booksByGenere->end(); ++it){
        for (Book* book : *it->second){
            if (book->getName().compare(bookName)==0){
                if(book->getcurrentlyOnInventory())
                return book;
            }
        }
    }
    return nullptr;

}

string Client:: getInventory(string topic) {
    string temp="";
    if(booksByGenere->at(topic)== nullptr)
        return "";
    for  (Book* book : *(booksByGenere->at(topic))){
        if (book->getcurrentlyOnInventory()){
            temp=temp+book->getName()+",";
        }
    }
    string answer=getName()+":"+temp.substr(0,temp.size()-1);
    cout<<"user inventory:"+answer<<endl;
    return answer;
}

Book* Client::containedBeforeBook(string bookName) {
    for (auto it =  booksByGenere->begin(); it != booksByGenere->end(); ++it){
        for (Book* book : *it->second){
            if (book->getName()==bookName & !book->getcurrentlyOnInventory()){
                return book;
            }
        }
    }
    return nullptr;

}

//login 132.72.45.155:7777 left 12
void Client::removeBook(string genere,Book * book) {
    cout<<"enterd remove book "+book->getName()<<endl;
    vector<Book*>::iterator iter;
    if (booksByGenere->count(genere)>0){
        cout<<"גאנר מופיע "<<endl;
        for (iter = booksByGenere->at(genere)->begin() ; iter <booksByGenere->at(genere)->end();++iter){
            if ((*iter)->getName() == book->getName()){
                cout<<"i setted the book "+book->getName()+"to false"<<endl;
                (*iter)->setcurrentlyOnInventory(false);}
        }
    }
}

Book* Client::getFromBooksByGenere(string gen,string bookName){

    if(booksByGenere->count(gen)==0)
        return nullptr;
    for(Book* b: *booksByGenere->at(gen)){
        if(b->getName()==bookName)
            return b;
    }
}
void Client::printInventory(){
    for (auto it = booksByGenere->begin(); it != booksByGenere->end(); ++it){
        for (int i=0; i< (it)->second->size();++i){
            cout<<"["+(*it).second->at(i)->getName()+"]"<<endl;
        }
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

void Client::clearClient(){
    for (auto it = booksByGenere->begin(); it != booksByGenere->end(); ++it){
        for (int i=0; i< (it)->second->size();++i){
            delete((*it).second->at(i));
        }
        delete((*it).second);
    }
    for (int i=0;i<wishList->size();++i){
        delete(wishList->at(i));
    }
}




