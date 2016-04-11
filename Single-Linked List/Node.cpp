//
// Created by Viktor Hellman on 10/04/16.
//

#include <cassert>
#include "node.h"

Node::Node (int nodeVal, Node *nextPtr)
        : value (nodeVal), nextPoint (nextPtr)
{
    //cout << "Constructor Node" << std::endl;
}

// Insert x into new node
Node* Node::insert (int x)
{
    nextPoint = new Node (x, nextPoint);
    assert(nextPoint != nullptr);
    return nextPoint;
}