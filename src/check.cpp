//
// Created by magami@wincs.cs.bgu.ac.il on 12/01/2020.
//
#include <boost/algorithm/string.hpp>dc++.h>
#include <Client.h>
#include "connectionHandler.h"
using namespace std;
#include <iostream>
#include "check.h"

int main () {

   string message = "message\nsubscription:78\nMessage-id:00021\ndestination:sci-fi\n\nBob wish to borrow Dune\n^@";
    vector<string> words1;
    boost::split(words1,message," ");
    cout<< words1[3];
    cout<< words1[4];
    cout<< words1[5];

}
