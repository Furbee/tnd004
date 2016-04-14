//
// Created by Oscar Nord on 07/04/16.
//

#include "Set.h"

template<typename T>
Set<T>::Set() {
    head = new Node();
    tail = head;
}

template <typename T>
Set<T>::Set(T a){
    head = new Node();
    tail = new Node(T());
    T *temp = new Node(a, tail, head);

}

template<typename T>
Set<T>::Set(T a[], int n) {
    head = new Node();
    for(int i = 0; i < n ; i++){
        //new Node(a[i], , head;)

    }

}

template<typename T>
Set<T>::Set(const Set &b) {

}

template <typename T>
Set<T>::~Set() {

}

template<typename T>
const T &Set<T>::operator=(const Set &b) {
    return; //<#initializer#>;
}

template<typename T>
bool Set<T>::is_empty() const {
    if(!head->next)  return true;

    return false;
}

template<typename T>
int Set<T>::cardinality() const {
    return 0;
}

template<typename T>
bool Set<T>::is_member(T val) const {
    return false;
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

template <typename T>
std::ostream& operator<<(std::ostream& os, const T& b){
    if(b.is_empty()){
        os << "Set is empty!" << std::endl;
        return os;
    }
    else{
        T* temp = b.head->next;
        while(temp->next != b.tail){
            os << temp->value << " ";
            temp == temp->next;
        }
        os << std::endl;
        return os;

    }
}






















