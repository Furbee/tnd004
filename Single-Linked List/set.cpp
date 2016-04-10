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

    Node* temp = head;

    if(head->nextPoint == nullptr)
        Node* xNode = new Node(x, nullptr);

    else {
        while (temp->nextPoint) {
            if (x > temp->nextPoint->value) {
                temp = temp->nextPoint;
            }
            if (x == temp->nextPoint->value) break;
            if (x < temp->nextPoint->value) {
                Node* xNode = new Node(x, temp->nextPoint);
                temp->nextPoint = xNode;
                break;
            }
        }
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


}

//Destructor: deallocate all nodes
Set::~Set ()
{

}

//Test if set is empty
bool Set::empty () const
{
    if(!head->nextPoint)
        return true;
    else
        return false;

}

//Return number of elements in the set
int Set::cardinality() const
{


}

//Test if x is an element of the set
bool Set::member (int x) const
{

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