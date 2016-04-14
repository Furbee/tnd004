//
// Created by Oscar Nord on 07/04/16.
//

#include "Set.h"

template<typename T>
Set<T>::Set() {

}

template<typename T>
Set<T>::Set(T *a, int n) {

}

template<typename T>
Set<T>::Set(const Set &b) {

}


Set::~set() {

}

template<typename T>
const Set &Set<T>::operator=(const Set &b) {
    return <#initializer#>;
}

template<typename T>
bool Set<T>::is_empty() const {
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





















