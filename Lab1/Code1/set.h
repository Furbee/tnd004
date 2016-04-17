//
// Created by Oscar Nord on 07/04/16.
//

#ifndef LAB1_SET_H
#define LAB1_SET_H

#include <iostream>
#include <memory>

template< typename T>
class Set {

private:

    class Node
    {
    public:

        //Constructor
        Node (const T& nodeVal = T(), std::shared_ptr<Node> nextPtr = std::make_shared<Node>(nullptr),
              std::shared_ptr<Node> prevPtr = std::make_shared<Node>())
                : value (nodeVal), next (nextPtr), prev(prevPtr)
        {};

        T value;
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;  //waek_ptr<...>()

    };

public:
    // Constructor
    Set();

    //TODO: Move constructor
    Set (T& a);

    

    //Constructor to create a Set from a sorted array
    Set (T a[], int n);

    //Copy constructor
    Set (const Set& b);

    // Destructor
    ~Set();

    //Assignment operator
    const T& operator=(Set b);


    //Test whether a set is empty
    bool is_empty () const;


    //Return number of elements in the set
    int cardinality() const;


    //Test set membership
    bool is_member (T& val) const;


    //Return true, if the set is a subset of b, otherwise false
    bool operator<=(const Set& b) const;


    //Return true, if the set is equal to set b
    bool operator==(const Set& b) const;


    //Return true, if the set is a strict subset of S, otherwise false
    bool operator<(const Set& b) const;



private:

    std::shared_ptr<Node> head;  //header Node
    std::shared_ptr<Node> tail;  //tail Node
    int counter; //number of elements Set

    //initialize a set
    void initSet();

    //Print
    void print(std::ostream& os) const;

    //insert
    Set& insert(std::shared_ptr<Node> p, T& val);


    friend std::ostream& operator<<(std::ostream& os, const Set<T> & b){
        if(b.is_empty()){
            os << "Set is empty!" << std::endl;
            return os;
        }
        else {
            b.print(os);
            return os;
        }
    }
};


/*******************************************************************************************************
'                                     Implementation of Functions
*******************************************************************************************************/


template <typename T>
Set<T>::Set()
//   : //TODO: FIX THIS SHIT
{
    initSet();
}


template <typename T>
Set<T>::Set(T& a){
    initSet();

    insert(tail,a);
}

template<typename T>
Set<T>::Set(T& a[], int n) {
    initSet();

    for(int i = 0; i < n ; i++){
        insert(tail, a[i]); //new Node(a[i], , head;)
    }

}

template<typename T>
Set<T>::Set(const Set &b) {

}

template <typename T>
Set<T>::~Set() {


}

template<typename T>
bool Set<T>::is_empty() const {
    if(!head->next) return true;
    else
        return false;
}

template<typename T>
int Set<T>::cardinality() const {
    return 0;
}

template<typename T>
bool Set<T>::is_member(T& val) const {
    return false;
}

template<typename T>
void Set<T>::initSet(){
    head = std::make_shared<Node>();
    tail = std::make_shared<Node>();
    head->next = tail;
    tail->prev = head;
    counter = 0;
}

template <typename T>
Set<T>& Set<T>::insert(std::shared_ptr<Node> p, T& val) {

    std::shared_ptr<Node> node = std::make_shared<Node>(val, p, p->prev);
    p->prev->next = p->prev = node;
    counter++;

    return *this;
}
/*
template <typename T>
Set<T>::make_empty(){
    while(head->next != tail){

    }
}
*/

template<typename T>
void Set<T>::print(std::ostream& os) const {

    if(counter == 0){

        std::cout << "Set is empty" << std::endl;
    }
    else{
        std::shared_ptr<Node> tempNode = head->next;
        while(tempNode->next){
            os << tempNode->value << " ";
            tempNode = tempNode->next;
        }
        os << std::endl;
    }
}

template<typename T>
const T &Set<T>::operator=(const Set &b) {
    return;
}


template<typename T>
bool Set<T>::operator<=(const Set &b) const {
    return false;
}

template<typename T>
bool Set<T>::operator==(const Set &b) const {
    return false;
}

template<typename T>
bool Set<T>::operator<(const Set &b) const {
    return false;
}

#endif //LAB1_SET_H
