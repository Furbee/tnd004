//
// Created by Oscar Nord on 07/04/16.
//

#ifndef LAB1_SET_H
#define LAB1_SET_H



#include <iostream>
#include <memory>
#include <utility>
#include <cstdio>

template< typename T>
class Set {

private:

    class Node
    {
    public:

        //Constructor
        Node (const T& nodeVal = T{}, const std::shared_ptr<Node> nextPtr = nullptr,
             const std::shared_ptr<Node> prevPtr = nullptr)
                : value {nodeVal}, next {nextPtr}, prev{prevPtr} {}

        Node(const T&& nodeVal, const std::shared_ptr<Node> nextPtr = nullptr, const std::shared_ptr<Node> prevPtr = nullptr)
                : value{move(nodeVal)}, next{nextPtr}, prev{prevPtr} {}

        T value;
        std::shared_ptr<Node> next;
        std::weak_ptr<Node>   prev;  //weak_ptr<...>()

    };

public:
    //Default Constructor
    Set();

    //Constructor
    Set (const T& a);

    //Constructor to create a Set from a sorted array
    Set (T a[], int n);

    //Move constructor
    Set(Set&& b) noexcept;

    //Copy constructor
    Set (const Set& b);

    //Destructor
    ~Set() = default;

    //Test whether a set is empty
    bool _is_empty () const;

    void make_empty();

    //Return number of elements in the set
    int cardinality() const;

    //Test set membership
    bool is_member (const T& val);

    //Assignment operator
    const Set& operator=(Set b);
    const Set& operator+=(const Set& b);
    const Set& operator*=(const Set & b);
    const Set& operator-=(const Set & b);

    //Overloaded operators: mixed-mode arithmetic
    //Set<T>& operator+(const Set<T> &a) const;
    //Set<T>& operator-(const Set<T> &a) const;

    // Overloaded operators: comparison
    bool operator<=(const Set& b) const;
    bool operator==(const Set& b) const;
    bool operator<(const Set& b) const;
    bool operator!=(const Set& b) const;


    friend Set<T> operator+(Set<T> s, const Set<T>& b) {
        //Set<T> newSet(s);
        return s += b;
    };

    friend Set operator*(Set<T> s, const Set<T>& b) {
        //Set<T> newSet(s);
        return s *= b;
    };

    friend Set operator-(Set<T> s, const Set<T>& b) {
        //Set<T> newSet(s);
        return s -= b;
    };

private:

    std::shared_ptr<Node> head;  //header Node
    std::shared_ptr<Node> tail;  //tail Node
    int counter = 0; //number of elements Set

    //Print
    void print(std::ostream& os) const;

    //insert
    void _insert(std::shared_ptr<Node> p, const T& val);

    void remove_node(std::shared_ptr<Node> node);


    friend std::ostream& operator<<(std::ostream& os, const Set<T> & b){
        if(b._is_empty()){
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
Set<T>::Set() {
    head = std::make_shared<Node>();
    tail = std::make_shared<Node>();

    head->next = tail;
    tail->prev = head;

    counter = 0;
}


template <typename T>
Set<T>::Set(const T& a) : Set() {
    _insert(head,a);
}

template<typename T>
Set<T>::Set(Set&& b) noexcept : head(std::move(b.head)), tail(std::move(b.tail)) {
    counter = b.counter;
    b.head = nullptr;
    b.tail = nullptr;
}


template<typename T>
Set<T>::Set(T a[], int n) : Set() {
    int i = 0;
    auto node = head;

    while(i < n){
        _insert(node, a[i++]);
        node = node->next;
    }
}

template<typename T>
Set<T>::Set(const Set &b) : Set() {

    auto node = head;
    auto node_b = b.head->next;

    while(node_b->next != nullptr){
        _insert(node, node_b->value);
        node_b = node_b->next;
        node = node->next;
    }
}

template<typename T>
bool Set<T>::_is_empty() const {
    if(!head->next) return true;
    else
        return false;
}

template<typename T>
int Set<T>::cardinality() const {
    return counter;
}

template<typename T>
bool Set<T>::is_member(const T& val) {
    auto node = head->next;
    while(node != tail){
        if (node->value == val) {
            return true;
        }
        else
            node = node->next;
    }
    return false;
}


template <typename T>
void Set<T>::_insert(std::shared_ptr<Node> node, const T& val) {

    auto temp = std::make_shared<Node>(val , node->next , node);
    node->next->prev = temp;
    node->next = temp;

    counter++;
}


template <typename T>
void Set<T>::make_empty(){
    while(head->next != tail){
        remove_node(head->next);
    }
}

template <typename T>
void Set<T>::remove_node(std::shared_ptr<Node> node){
    auto pre = node->prev.lock();
    pre->next = node->next;
    node->next->prev = node->prev;
    counter--;

}

template<typename T>
void Set<T>::print(std::ostream& os) const {
    std::cout << "Counter: " << counter << std::endl;
    if(counter == 0){

        std::cout << "Set is empty" << std::endl;
    }

    else{

        auto tempNode = head->next;
        while(tempNode->next){
            os << tempNode->value << " ";
            tempNode = tempNode->next;
        }
        os << std::endl;
    }
}

template<typename T>
const Set<T>& Set<T>::operator=(Set b) {
    std::swap(head, b.head);
    std::swap(tail, b.tail);
    counter = b.counter;

    return *this;
}


template <typename T>
const Set<T>& Set<T>::operator*=(const Set& b){
    auto newSet = head;
    auto bSet = b.head;

    while(newSet->next != tail){
        if(bSet->next == b.tail) {
            remove_node(newSet->next);
        }
        else if(bSet->next->value > newSet->next->value){
                remove_node(newSet->next);
        }
        else if(bSet->next->value == newSet->next->value){
            newSet = newSet->next;
        }
        else
            bSet = bSet->next;
    }
    return *this;
}



template <typename T>
const Set<T>& Set<T>::operator+=(const Set<T> &b){

    if(!head->next) return b;
    if(!b.head->next) return *this;

    auto setOne = head->next;
    auto setTwo = b.head->next;

    while(setOne != tail && setTwo != b.tail){
        if(setOne->value < setTwo->value){
            setOne = setOne->next;
        }
        else if( setOne->value == setTwo->value){
            setOne = setOne->next;
            setTwo = setTwo->next;
        }
        else if(setOne->value > setTwo->value){
            _insert(setOne->prev.lock(), setTwo->value);
            setTwo = setTwo->next;
        }
        else if(setOne == tail /*&& setTwo != b.tail*/){
            setOne = setOne->prev.lock();
            setOne->next = setTwo;
            setTwo->prev = setOne;
            return *this;
        }
        else { return *this; }
    }
    return *this;
}


template <typename T>
const Set<T>& Set<T>::operator-=(const Set & b){

    if(!b.head->next) return *this;

    auto setOne = head->next;
    auto setTwo = b.head->next;

    while(setOne != tail){
        if(setTwo == b.tail /*&& setTwo != b.tail*/){
            return *this;
        }
        else if(setOne->value < setTwo->value){
            setOne = setOne->next;
        }
        else if(setOne->value > setTwo->value){
            setTwo = setTwo->next;
        }
        else if( setOne->value == setTwo->value){
            remove_node(setOne);
            //setOne = setOne->next;
            setTwo = setTwo->next;
        }
    }
    return *this;
}


template<typename T>
bool Set<T>::operator<=(const Set &b) const {

    auto toCheck = b.head->next;
    auto newSet = head->next;
    if(b._is_empty() || _is_empty()) return false;
    while(toCheck->next != b.tail){
        if(newSet->next == tail) return true;
        if(newSet->value == toCheck->value){
            newSet = newSet->next;
            toCheck = toCheck->next;
        }
        else toCheck = toCheck->next;
    }
    return false;

}

template<typename T>
bool Set<T>::operator==(const Set &b) const {
    if(*this <= b && b <= *this) {
        return true;
    }
    return false;
}

template<typename T>
bool Set<T>::operator<(const Set &b) const {
    if(*this <= b && !(b <= *this)) {
        return true;
    }
    return false;
}

template<typename T>
bool Set<T>::operator!=(const Set &b) const {
    if(b == *this) {
        return false;
    }
    return true;


}

#endif //LAB1_SET_H
