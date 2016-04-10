//
// Created by Viktor Hellman on 10/04/16.
//

#ifndef SINGLE_LINKED_LIST_NODE_H
#define SINGLE_LINKED_LIST_NODE_H


#include <iostream>

class Set;

class Node {
private:
    int value = 0;
    Node* nextPoint = nullptr;
public:
    Node(int, Node*);

friend std::ostream& operator<< (std::ostream& os, const Set& theSet);
friend class Set;
};

#endif //SINGLE_LINKED_LIST_NODE_H
