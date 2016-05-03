
/*
  Author: Aida Nordman
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




    unsigned int getSize(){
        return _size;
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

    void rehash();
    unsigned search_empty_slot(unsigned tmp_hash);
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
        : _size(nextPrime(table_size)), nItems(0), nDeleted(0), total_visited_slots(0), count_new_items(0), h(f)
{
    hTable = new Item<Key_Type, Value_Type>*[nextPrime(table_size)]();
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
    auto tmp_hash = h(key, _size);


    //if slot is empty keys does not exist
    if (!hTable[tmp_hash]){
        cout << "Key not found!";
    }

    //if slot is occupied but does not equal key
    else if(hTable[tmp_hash] && hTable[tmp_hash]->get_key() != key){
        cout << "Slot occupied" << endl <<"Searching proximal slots." << endl;

        unsigned emptySlot = search_empty_slot(tmp_hash);

        for(tmp_hash++ ; tmp_hash < emptySlot ; tmp_hash++ ) {  //check all slots up to emptySlot
            if(hTable[tmp_hash]->get_key() == key){
                cout << "_find found " << "key: '" << key << "', with value: " << hTable[tmp_hash]->get_value() << endl;
                return &hTable[tmp_hash]->get_value();
            }
        }
        return nullptr;
    }

    //slot is occupied by key
    else {
        cout << "_find found " << "key: '" << key << "', with value: " << hTable[tmp_hash]->get_value() << endl;
        return &hTable[tmp_hash]->get_value();
    }
    // key not found
    return nullptr;
}


//Insert the Item (key, v) in the table
//If key already exists in the table then change the value associated with key to v
//Re-hash if the table reaches the MAX_LOAD_FACTOR
template <typename Key_Type, typename Value_Type>
void HashTable<Key_Type, Value_Type>::_insert(const Key_Type& key, const Value_Type& v)
{
    auto tmp_hash = h(key, _size);

    //if key already exists at given slot
    if(hTable[tmp_hash] && hTable[tmp_hash]->get_key() == key){
        hTable[tmp_hash]->set_value(v);                                       //change value at key
        total_visited_slots++;

        cout << "Value updated" << endl;
        return;
    }

    //if slot is occupied by another key with same hash-index
    else if(hTable[tmp_hash]){
        cout << "Slot occupied by: " << hTable[tmp_hash]->get_key() << endl
             << "Searching for new slot..." << endl;
        tmp_hash = search_empty_slot(tmp_hash) % _size;                              //return new slot to insert item in.
        add_new_Item(tmp_hash, key, v);
    }

    else {
         add_new_Item(tmp_hash, key, v);
    }

    //check if loadfactor gets larger than allowed
    if(loadFactor() >= MAX_LOAD_FACTOR) { rehash(); }

    return;
}


//Remove Item with key, if the item exists
//If an Item was removed then return true
//otherwise, return false
template <typename Key_Type, typename Value_Type>
bool HashTable<Key_Type, Value_Type>::_remove(const Key_Type& key) {
    //IMPLEMENT
    auto tmpHash = h(key, _size);
    if(_find(key) == nullptr) {

        cout << "Key not found!." << endl << "Aborting." << endl;
        return false;
    }
    else{
        hTable[tmpHash] = Deleted_Item<Key_Type, Value_Type>::get_Item();

        total_visited_slots++;
        nItems--;
        nDeleted++;

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

template <typename Key_Type, typename Value_Type>
void HashTable<Key_Type, Value_Type>::rehash() {

    auto OldhTable = hTable;
    int OldSize = _size;

    nItems = 0;

    _size = nextPrime(OldSize * 2);
    hTable = new Item<Key_Type, Value_Type>*[_size]();

    //Copy to new Table
    for (size_t i = 0; i < OldSize; i++) {
        if (OldhTable[i] != nullptr && OldhTable[i] != Deleted_Item<Key_Type, Value_Type>::get_Item()) {
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
}

//searches for for next empty slot after index tmp_hash
template <typename Key_Type, typename Value_Type>
unsigned HashTable<Key_Type, Value_Type>::search_empty_slot(unsigned tmp_hash) {
    unsigned i = tmp_hash;

    while ( hTable[i]) {
        i++;
        cout << "Slot tested:" << i % _size << ". ";
        total_visited_slots++;
    }
    cout << endl << "Slot found at " << i %_size << endl;
    cout << endl;
    return i;

}

//add a new Item to the HashTable,
template <typename Key_Type, typename Value_Type>
void HashTable<Key_Type, Value_Type>::add_new_Item(const unsigned& idx, const Key_Type& key, const Value_Type& val){
    hTable[idx] = new Item<Key_Type, Value_Type>(key, val);
    nItems++;
    count_new_items++;
}

template <typename Key_Type, typename Value_Type>
Value_Type& HashTable<Key_Type, Value_Type>::operator[](const Key_Type& key) {


    return nullptr;
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


