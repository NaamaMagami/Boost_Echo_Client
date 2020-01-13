//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "Book.h"
Book::Book(string _name,string _previousOwner,string gen):name(_name),originalOwner(_previousOwner),genere(gen),currentOwner(_originalOwner){}

void Book::changeOwner(string newOwner){
    currentOwner=newOwner;
};

const string &Book::getName() const {
    return name;
}

const string &Book::getpreviousOwner() const {
    return originalOwner;
}

const string &Book::getCurrentOwner() const {
    return currentOwner;
}

const string &Book::getGenere() const {
    return genere;
}
