//
// Created by Oscar Nord on 07/04/16.
//

#ifndef LAB1_SET_H
#define LAB1_SET_H

#include <iostream>

template< typename T>
class Set {

public:
    // Constructors
    Set();

    //TODO: Move constructor
    Set (T a);

    //Constructor to create a Set from a sorted array
    Set (T a[], int n);

    //Copy constructor
    Set (const Set& b);

    // Destructor
    ~Set();


    //Assignment operator
    const T& operator=(const Set& b);


    //Test whether a set is empty
    bool is_empty () const;


    //Return number of elements in the set
    int cardinality() const;


    //Test set membership
    bool is_member (T val) const;


    //Return true, if the set is a subset of b, otherwise false
    //a <= b if every member of a is a member of b
    bool operator<=(const Set& b) const;


    //Return true, if the set is equal to set b
    //a == b, if a <= b but not b <= a
    bool operator==(const Set& b) const;


    //Return true, if the set is a strict subset of S, otherwise false
    //a < b iff a <= b but not b <= a
    bool operator<(const Set& b) const;


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

    Node *head;  /**< Pointer to the dummy header Node */
    Node *tail;  /**< Pointer to the dummy tail Node */
    int counter; /**< Count number of elements in the Set */

    friend std::ostream& operator<<(std::ostream& os, const Set& b);
};



#endif //LAB1_SET_H
