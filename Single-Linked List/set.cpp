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


}

//Constructor creating a set
//from n integers in a non-sorted array a
Set::Set (int a[], int n)
{

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
    if (!head->next)
        return true;

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

ostream& operator<< (ostream& os, const Set& theSet)
{

}