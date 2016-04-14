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

    //Constructor to create a Set from a sorted array
    Set (T a[], int n);

    //Copy constructor
    Set (const Set& b);

    // Destructor
    ~set();


    //Assignment operator
    const Set& operator=(const Set& b);


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

    //Private member functions

    /** \brief Insert a new Node storing val before the Node pointed by p
     *
     * \param p pointer to a Node
     * \param val value to be inserted  before position p
     * \return *this
     *
     */
    //Insert a new Node storing val before the Node pointed by p
    Set& insert(Node *p, T val);


    /** \brief Remove the Node pointed by p
    *
    * \param p pointer to a Node
    * \return *this
    *
    */
    //Remove the Node pointed by p
    Set& erase(Node *p);


    /** \brief Initialize the Set to an empty Set
    *
    * \return None
    *
    */
    //Initialize the Set to an empty Set
    void init();


    /** \brief Display the Set to ostream os
    *
    * \note This function does not modify *this in any way
    * \return None
    *
    */
    //Display the Set to ostream os
    void print(std::ostream& os) const;


    /** \brief Set union of *this with Set S
    *
    * \param S a Set
    * \note This function does not modify *this nor S in any way
    * \return A new Set representing the union of *this with Set S
    *
    */
    //Return a new set with the elements in S1 or in S2 (without repeated elements)
    Set _union(const Set& S) const;


    /** \brief Set intersection of *this with Set S
    *
    * \param S a Set
    * \note This function does not modify *this nor S in any way
    * \return A new Set representing the intersection of *this with Set S
    *
    */
    //Return a new set with the elements in both sets S1 and S2
    Set _intersection(const Set& S) const;


    /** \brief Set difference of *this with Set S
    *
    * \param S a Set
    * \note This function does not modify *this nor S in any way
    * \return A new Set representing the difference of *this with Set S
    *
    */
    //Return a new set with the elements in set S1 that do not belong to set S2
    Set _difference(const Set& S) const;



    //overloaded operators: union, intersection, difference, operator<<


    /** \brief Overloaded operator<<
     *
     * \param os output stream
     * \param b Set to be displayed
     * \return parameter os
     *
     */
    friend std::ostream& operator<< (std::ostream& os, const Set<T>& b)
    {
        if (b.is_empty ())
            os << "Set is empty!" << std::endl;
        else
        {
            b.print(os); //call the private function Set<T>::print
        }

        return os;
    }


    /** \brief Overloaded operator+: to represent Set union S1+S2
     *
     * S1+S2 is the Set of elements in Set S1 or in Set S2 (without repeated elements)
     * \param S1 a Set
     * \param S2 a Set
     * \note This function does not modify S1 nor S2 in any way
     * \return A new Set representing the union of S1 with S2, S1+S2
     *
     */
    friend Set<T> operator+ (const Set<T>& S1, const Set<T>& S2)
    {
        return S1._union(S2); //call the private function Set<T>::_union
    };



    /** \brief Overloaded operator*: to represent Set intersection S1*S2
     *
     * S1*S2 is the Set of elements in both Sets S1 and set S2
     * \param S1 a Set
     * \param S2 a Set
     * \note This function does not modify S1 nor S2 in any way
     * \return A new Set representing the intersection of S1 with S2, S1*S2
     *
     */
    friend Set<T> operator* (const Set<T>& S1, const Set<T>& S2)
    {
        return S1._intersection(S2); //call the private function Set<T>::_intersection
    };


    /** \brief Overloaded operator-: to represent Set difference S1-S2
     *
     * S1-S2 is the Set of elements in Set S1 that do not belong to Set S2
     * \param S1 a Set
     * \param S2 a Set
     * \note This function does not modify S1 nor S2 in any way
     * \return A new Set representing the set difference S1-S2
     *
     */
    friend Set<T> operator- (const Set<T>& S1, const Set<T>& S2)
    {
        return S1._difference(S2); //call the private function Set<T>::_difference
    }
    
};


#endif //LAB1_SET_H
