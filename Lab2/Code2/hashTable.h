
/*
  Author: Viktor Hellman och Oscar Nord
  Course: TND004, Lab 2
  Description: template class HashTable represents an open addressing hash table
              (also known as closed_hashing) with linear probing
*/

#include "Item.h"

#include <iostream>
#include <iomanip>

using namespace std;

const int NOT_FOUND = -1;
const double MAX_LOAD_FACTOR = 0.5;


//Template class to represent an open addressing hash table using linear probing to resolve collisions
//Internally the table is represented as an array of pointers to Items
template <typename Key_Type, typename Value_Type>
class HashTable
{
public:

    //New type HASH: pointer to a hash function
    typedef unsigned (*HASH)(Key_Type, int);


    //Constructor to create a hash table
    //table_size is number of slots in the table (next prime number is used)
    //f is the hash function
    HashTable(int table_size, HASH f);


    //Destructor
    ~HashTable();


    //Return the load factor of the table, i.e. percentage of slots in use or deleted
    double loadFactor() const
    {
        return (double) (nItems+nDeleted) / _size;
    }


    //Return number of items stored in the table
    unsigned get_number_OF_items() const
    {
        return nItems;
    }

    //Return the total number of visited slots (during search, insert, remove, or re-hash)
    unsigned get_total_visited_slots() const
    {
        return total_visited_slots;
    }

    //Return the total number of call to new Item()
    unsigned get_count_new_items() const
    {
        return count_new_items;
    }


    //Return a pointer to the value associated with key
    //If key does not exist in the table then nullptr is returned
    const Value_Type* _find(const Key_Type& key);


    //Insert the Item (key, v) in the table
    //If key already exists in the table then change the value associated with key to v
    //Re-hash if the table reaches the MAX_LOAD_FACTOR
    void _insert(const Key_Type& key, const Value_Type& v);


    //Remove Item with key, if the item exists
    //If an Item was removed then return true
    //otherwise, return false
    bool _remove(const Key_Type& key);

    //Overloaded subscript operator
    //If key is not in the table then insert a new Item = (key, Value_Type())
    Value_Type& operator[](const Key_Type& key);


    //Display all items in table T to stream os
    friend ostream& operator<<(ostream& os, const HashTable& T)
    {
        for (unsigned i = 0; i < T._size; ++i)
        {
            if (T.hTable[i] && T.hTable[i] != Deleted_Item<Key_Type,Value_Type>::get_Item())
            {
                os << *T.hTable[i] << endl;
            }
        }

        return os;
    }


    //Display the table for debug and testing purposes
    //Thus, empty and deleted entries are also displayed
    void display(ostream& os);


private:
   /** ************************************************************************************ *
    *                                   Data members                                        *
    ** **************************************************************************************/

    //Number of slots in the table, a prime number
    unsigned _size;

    //Hash function
    const HASH h;

    //Number of items stored in the table
    //Instances of Deleted_Items are not counted
    unsigned nItems;

    //Number of slots that are marked as deleted
    unsigned nDeleted;

    //Table is an array of pointers to Items
    //Each slot of the table stores a pointer to an Item =(key, value)
    Item<Key_Type, Value_Type>** hTable;

    //Some statistics
    unsigned total_visited_slots;  //total number of visited slots
    unsigned count_new_items;      //number of calls to new Item()


    /* ************************************************************************************ *
     *                           Auxiliar member functions                                  *
    ** ************************************************************************************ */

    //Disable copy constructor!!
    HashTable(const HashTable &) = delete;

    //Disable assignment operator!!
    const HashTable& operator=(const HashTable &) = delete;

    //Item<Key_Type, Value_Type>* findItem(const Key_Type& key);
    unsigned findIndex(const Key_Type& key);
    void rehash();
    void delete_Item(const unsigned& idx);
    void add_new_Item(const unsigned &idx, const Key_Type& key, const Value_Type& val);
};


//Test if a number is prime
bool isPrime( int n );

//Return a prime number at least as large as n
unsigned nextPrime( int n );


/* ************************************************************************************ *
*                           Member functions implementation                             *
** ************************************************************************************ */

//Constructor to create a hash table
//table_size number of slots in the table (next prime number is used)
//f is the hash function
template <typename Key_Type, typename Value_Type>
HashTable<Key_Type, Value_Type>::HashTable(int table_size, HASH f)
        : _size(nextPrime(table_size)), nItems(0), nDeleted(0), total_visited_slots(0), count_new_items(0), h(f),
        hTable( new Item<Key_Type, Value_Type>*[nextPrime(table_size)]() )
{
    //hTable = new Item<Key_Type, Value_Type>*[nextPrime(table_size)]();
}


//Destructor
template <typename Key_Type, typename Value_Type>
HashTable<Key_Type, Value_Type>::~HashTable()
{
    for (int i = 0; i < _size; i++) {
        if(hTable[i] != nullptr) {
            delete hTable[i];
        }
    }
    delete[] hTable;
}



//Return a pointer to the value associated with key
//If key does not exist in the table then nullptr is returned
template <typename Key_Type, typename Value_Type>
const Value_Type* HashTable<Key_Type, Value_Type>::_find(const Key_Type& key)
{
    auto tempHash = findIndex(key);

    if(hTable[tempHash] == nullptr) { return nullptr; }

    else{
        return hTable[tempHash]->get_value();
    }


    /*auto tmp_hash = h(key, _size);



    //if slot is empty keys does not exist
    if (!hTable[tmp_hash]){
        total_visited_slots++;

        // key not found
        return nullptr;
    }

    //if slot is occupied but does not equal key
    else if(hTable[tmp_hash] && hTable[tmp_hash]->get_key() != key){
        unsigned emptySlot = search_empty_slot(tmp_hash);

        for(tmp_hash++ ; tmp_hash < emptySlot ; tmp_hash++ ) {  //check for key at all slots up to emptySlot
            total_visited_slots++;
            if(hTable[tmp_hash]->get_key() == key){ return &hTable[tmp_hash]->get_value(); }
        }
        return nullptr; //if not found before an emptyslot, it doesn't exist.
    }

    //slot is occupied by key
    else { return &hTable[tmp_hash]->get_value(); }*/
}


//Insert the Item (key, v) in the table
//If key already exists in the table then change the value associated with key to v
//Re-hash if the table reaches the MAX_LOAD_FACTOR
template <typename Key_Type, typename Value_Type>
void HashTable<Key_Type, Value_Type>::_insert(const Key_Type& key, const Value_Type& v)
{
    auto tempHash = findIndex(key);

    if( hTable[tempHash] != nullptr ) { //value found, update and quit.
            hTable[tempHash]->set_value(v);
            return;
    }

    //if value not found, insert new Item at tmp_hash
    add_new_Item(tempHash, key, v);


    //check if loadfactor gets larger than allowed
    if(loadFactor() >= MAX_LOAD_FACTOR) { rehash(); }

    return;
}


//Remove Item with key, if the item exists
//If an Item was removed then return true
//otherwise, return false
template <typename Key_Type, typename Value_Type>
bool HashTable<Key_Type, Value_Type>::_remove(const Key_Type& key) {
    auto tempHash = findIndex(key);

    if(hTable[tempHash] == nullptr) { return false; }

    else{
        delete_Item(tempHash);
        return true;
    }
}


//Display the table for debug and testing purposes
//This function is used for debugging and testing purposes
//Thus, empty and deleted entries are also displayed
template <typename Key_Type, typename Value_Type>
void HashTable<Key_Type, Value_Type>::display(ostream& os)
{
    os << "-------------------------------\n";
    os << "Number of items in the table: " << get_number_OF_items() << endl;
    os << "Load factor: " << fixed << setprecision(2) << loadFactor() << endl;

    os << "Unique items: " << count_new_items << endl;
    os << "nItems: " << nItems << endl;

    for (unsigned i = 0; i < _size; ++i)
    {
        os << setw(6) << i << ": ";

        if (!hTable[i]) {
            os << "null" << endl;
        }
        else if (hTable[i] == Deleted_Item<Key_Type, Value_Type>::get_Item()) {
            os << "deleted" << endl;
        }
        else {
            os << *hTable[i]
               << "  (" << h(hTable[i]->get_key(),_size) << ")" << endl;
        }
    }

    os << endl;
}


/* ************************************************************************************ *
 *                           Auxiliar member functions                                  *
** ************************************************************************************ */
template<typename Key_Type, typename Value_Type>
unsigned HashTable<Key_Type, Value_Type>::findIndex(const Key_Type& key){
    auto tempHash = h(key, _size);

    while(hTable[tempHash] != nullptr){
        if(hTable[tempHash]->get_key() == key){
            total_visited_slots++;
            return tempHash;
        }
        tempHash = ++tempHash %(_size);
        total_visited_slots++;
    }
    return tempHash;

}
//
//template<typename Key_Type, typename Value_Type>
//Item<Key_Type, Value_Type>* HashTable<Key_Type, Value_Type>::findItem(const Key_Type& key){
//    auto tempHash = h(key, _size);
//
//    while(hTable[tempHash] != nullptr){
//        if(hTable[tempHash]->get_key() == key){
//            return hTable[tempHash];
//        }
//        tempHash = ++tempHash %(_size);
//        total_visited_slots++;
//    }
//    return nullptr;
//
//}

template <typename Key_Type, typename Value_Type>
void HashTable<Key_Type, Value_Type>::rehash() {
    cout << endl << "Attemptning rehash" << endl;
    auto OldhTable = hTable;
    int OldSize = _size;

    _size = nextPrime(OldSize * 2); //define new size as a primenumber
    hTable = new Item<Key_Type, Value_Type>*[_size]();
    nItems = 0;
    nDeleted = 0;
    count_new_items = 0;

    //Copy to new Table
    for (size_t i = 0; i < OldSize; i++) {
        if ( OldhTable[i] != nullptr && OldhTable[i] != Deleted_Item<Key_Type, Value_Type>::get_Item() ) {
            _insert(OldhTable[i]->get_key(), OldhTable[i]->get_value());
        }
    }

    // delete old Table
    for (size_t i = 0; i < OldSize; i++) {
        if(OldhTable[i] != nullptr) {
            delete OldhTable[i];
        }
    }
    delete[] OldhTable;
    cout << endl << "Rehash completed" << endl;
}

//add a new Item to the HashTable, add to appropriate values
template <typename Key_Type, typename Value_Type>
void HashTable<Key_Type, Value_Type>::add_new_Item(const unsigned& idx, const Key_Type& key, const Value_Type& val){
    hTable[idx] = new Item<Key_Type, Value_Type>(key, val);
    nItems++;
    count_new_items++;
}

template <typename Key_Type, typename Value_Type>
void HashTable<Key_Type, Value_Type>::delete_Item(const unsigned& idx){
        hTable[idx] = Deleted_Item<Key_Type,Value_Type>::get_Item();
        total_visited_slots++;
        nItems--;
        nDeleted++;
}

template <typename Key_Type, typename Value_Type>
Value_Type& HashTable<Key_Type, Value_Type>::operator[](const Key_Type& key) {

    auto temp = findIndex(key);

    if(hTable[temp] == nullptr){
        //_insert(key, Value_Type());
        add_new_Item(temp, key, Value_Type());
        return hTable[findIndex(key)]->get_value();
    }
    return hTable[temp]->get_value();
}


/* ************************************************************************************ *
 *                           Functions to find prime numbers                            *
* ************************************************************************************ */

//Test if a number is prime
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}


//Return a prime number at least as large as n
unsigned nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for(; !isPrime( n ); n += 2 );

    return n;
}


