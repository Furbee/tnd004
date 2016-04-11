//
// Created by Oscar Nord on 10/04/16.
//

#include "set.h"
#include <cassert>
#include <NEW>

//Default constructor
Set::Set ()
{
    head = new Node(0,nullptr);
}

//Insert
void Set::insert (int x){

    if(empty()){ // Tomt?
        head->nextPoint = head->insert(x); // Om så är fallet sätt in x efter dummy
    }
    else {
        Node* temp = head;
        while (temp->nextPoint){ // tittar en framåt
            if(x > temp->nextPoint->value)
            { // mindre gå vidare
                temp = temp->nextPoint;
            }
            else if	(x < temp->nextPoint->value)
            { // lägger till
                temp->insert(x);			 // insert function från node
                return;
            }
            else if(x == temp->nextPoint->value)
            { // om det redan finns
                return;
            }
        }

        temp->insert(x);
    }

}

//Constructor creating a set
//from n integers in a non-sorted array a
Set::Set (int a[], int n)
{
    head = new Node(0, nullptr);

    for( int i = 0 ; i < n ; i++ ){
        insert(a[i]);
    }
}

//copy constructor
Set::Set (const Set &source)
{
    head = new Node(0, nullptr);

    Node* node = source.head->nextPoint;
    Node* newNode = head;

    while(node) {
        newNode->nextPoint = new Node(node->value, nullptr);
        node = node->nextPoint;
        newNode = newNode->nextPoint;
    }
}

//Destructor: deallocate all nodes
Set::~Set ()
{
    while(head) {
        Node* temp = head->nextPoint;
        delete head;
        head = temp;
    }
    delete head;
}

//Test if set is empty
bool Set::empty () const
{
    if(!head->nextPoint)
        return true;

    return false;
}

//Return number of elements in the set
int Set::cardinality() const
{
    Node* node = this->head->nextPoint;

    int counter = 0;

    while(node){
        counter++;
        node = node->nextPoint;
    }

    return counter;
}

//Test if x is an element of the set
bool Set::member (int x) const
{
    Node* node = this->head->nextPoint;

    while(node){
        if(node->value == x){
            return true;
        }
        node = node->nextPoint;
    }
    return false;
}

//Test if R is subset of S
bool Set:: operator<=(const Set& b) const
{

}

//Test if R is subset of S and S is subset of R
bool Set:: operator==(const Set& b) const
{

}


//Test if R is proper subset of S
bool Set:: operator<(const Set& b)  const
{

}


//Set union
//Repeated values are not allowed
Set Set::operator+ (const Set& b) const
{

}

//Set intersection
Set Set::operator* (const Set& b) const
{


}

//Set difference
Set Set::operator- (const Set& b) const
{

}

//set union with set {x}
Set Set::operator+(int x) const
{

}

//set difference with set {x}
Set Set::operator-(int x) const
{

}

//Assignment operator
const Set& Set::operator=(const Set &s)
{


}

std::ostream& operator<< (std::ostream& os, const Set& theSet)
{
    if( theSet.empty() ) {
        os << "Set empty!" << std::endl;
        return os;
    }

    else{
        Node* temp = theSet.head->nextPoint;
        while( temp ){
            os << temp->value << " ";
            temp = temp->nextPoint;
        }
        os << std::endl;
        return os;
    }
}