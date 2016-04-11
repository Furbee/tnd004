//
// Created by Viktor Hellman on 10/04/16.
//

#ifndef SINGLE_LINKED_LIST_NODE_H
#define SINGLE_LINKED_LIST_NODE_H



#include <iostream>

using namespace std;

class Set;

class Node
{
public:
    Node (int, Node*);  // Constructor

    Node* insert (int x);

private:
    int value;
    Node* nextPoint;

    friend ostream& operator<< (ostream &os, const Set &theSet);
    friend class Set;
};


#endif //SINGLE_LINKED_LIST_NODE_H
