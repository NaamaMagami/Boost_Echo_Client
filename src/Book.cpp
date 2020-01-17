//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <iostream>
#include <utility>
#include "Book.h"
using namespace std;
Book::Book(string _name,string _previousOwner,string gen):name(std::move(_name)),previousOwner(std::move(_previousOwner)),genere(std::move(gen)),currentlyOnInventory(true){}
const string &Book::getName() const {
    return name;
}

Book::Book() noexcept:name(""),previousOwner("a"),genere(""),currentlyOnInventory(true){
    cout<<"empty CONSTTTTTTTTTTT"<<endl;
}

const string &Book::getpreviousOwner() const {
    return previousOwner;
}
string Book::setpreviousOwner(string owner)  {
    return previousOwner=std::move(owner);
}

const string &Book::getGenere() const {
    return genere;
}

const bool &Book::getcurrentlyOnInventory() const {
    return currentlyOnInventory;
}
void Book::setcurrentlyOnInventory(bool set) {
    currentlyOnInventory=set;
}

bool Book::empty() {
    return this->name.empty();
}

Book::Book(const Book & other)
    :name(other.name)
    ,currentlyOnInventory(other.currentlyOnInventory)
    ,genere(other.genere)
    ,previousOwner(other.previousOwner)
{
    cout<<"Copy !!!!!"<<endl;
}
Book::Book(Book && other) noexcept
        :name(move(other.name))
        ,currentlyOnInventory(other.currentlyOnInventory)
        ,genere(move(other.genere))
        ,previousOwner(move(other.previousOwner))
{
    cout<<"Move Bitch, get out of th way !!!!!"<<endl;
}