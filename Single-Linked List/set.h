//
// Created by Oscar Nord on 10/04/16.
//

#ifndef SINGLE_LINKED_LIST_SET_H
#define SINGLE_LINKED_LIST_SET_H

#include "node.h"
#include <iostream>

//using namespace std;

class Set {

public:
    //Constructor
    Set();

    //Creating a set from n-integers in a non sorted array
    Set (int a[], int n);
    //copy constructor
    Set (const Set &source);
    //Destructor
    ~Set();

    bool empty () const; //Test if the set is empty
    int cardinality() const; //Return number of elements in the set
    bool member (int x) const; //Test if x is an element of the set

    //Overloaded operators
    // A new set is returned by the operators
    Set operator+ (const Set& b) const; //Set union
    Set operator* (const Set& b) const; //Set intersection
    Set operator- (const Set& b) const; //Set difference
    Set operator+(int x) const; //set union with set {x}
    Set operator-(int x) const; //set difference with set {x}

    //Comparison operators
    bool operator<=(const Set& b) const;
    bool operator==(const Set& b) const;
    bool operator<(const Set& b) const;

    //assignment operator
    const Set& operator=(const Set& b);


private:
    Node *head; //points to the first node
    //Note: first node is a dummy node
    void insert (int x);

    friend std::ostream& operator<< (std::ostream& os, const Set& b);
};


#endif //SINGLE_LINKED_LIST_SET_H
