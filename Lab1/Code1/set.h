//
// Created by Oscar Nord on 07/04/16.
//

#ifndef LAB1_SET_H
#define LAB1_SET_H

template< typename T>
class Set {

public:
    // Constructors
    Set<int> T;

    Set<int> T(v); //create the set R = {v}

    //TODO: Move constructor

    Set<int> T(S); //Copy constructor initializing set R with set S


    // Destructor
    ~set();

private:

    class Node
    {
    public:

        //Constructor
        Node (T nodeVal = T(), Node* nextPtr = nullptr, Node* prevPtr = nullptr)
                : value (nodeVal), next (nextPtr), prev(prevPtr)
        {  };

        //Data members
        T value;    // Object (element) stored in the Node
        Node* next; // Pointer to the next Node
        Node* prev; // Pointer to the previous Node
    };


};


#endif //LAB1_SET_H
