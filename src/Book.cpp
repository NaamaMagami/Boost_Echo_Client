//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "Book.h"
Book::Book(string _name,string _previousOwner,string gen):name(_name),previousOwner(_previousOwner),genere(gen),currentlyOnInventory(true){}

void Book::changeOwner(string newOwner){
};

const string &Book::getName() const {
    return name;
}

const string &Book::getpreviousOwner() const {
    return previousOwner;
}
 string Book::setpreviousOwner(string owner)  {
     previousOwner=owner;
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