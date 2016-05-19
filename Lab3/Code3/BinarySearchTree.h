#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <mutex>          // std::mutex, std::lock
#include <memory>
#include <iomanip>
#include <vector>

using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  private:
    struct BinaryNode
    {
        Comparable element;
        shared_ptr<BinaryNode> left, right;
        weak_ptr<BinaryNode> parent;

        BinaryNode( const Comparable & theElement, shared_ptr<BinaryNode> lt, shared_ptr<BinaryNode> rt, weak_ptr<BinaryNode> pt )
          : element{ theElement }, left{ lt }, right{ rt }, parent{ pt }  { }

        BinaryNode( Comparable && theElement, shared_ptr<BinaryNode> lt, shared_ptr<BinaryNode> rt, weak_ptr<BinaryNode> pt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt }, parent{ pt } { }
    };

  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root, nullptr );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    void find_pred_succ(Comparable x, Comparable& low, Comparable& high) {
        auto current = root;
        //find_pre_success(current, x, low, high);
        crop_tree(current, high, low);

        cout << "Current: " << current->element << endl << endl;

        high = find_succes(current)->element;
        low = find_pre(current)->element;


        /*if( x < current->element) {
            high = current->element;
            low = find_pre(x,current->left)->element;
            }

        /*
        high = find_succes(x, current)->element;

        low = find_pre(x, current)->element;
        */
    }

    void crop_tree(shared_ptr<BinaryNode>& current, Comparable& high, Comparable& low){

        //if(current == nullptr) return;
        if(high < current->element && low < current->element){
            high = current->element;
            current = current->left;
            crop_tree(current, high, low);
        }
        if(high > current->element && low > current->element ){
            low = current->element;
            current = current->right;
            crop_tree(current, high, low);
        }
        return;
    }

    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }


    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable x )
    {
        weak_ptr<BinaryNode> parent = root;
        insert( x, root, parent );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        weak_ptr<BinaryNode> parent = root;
        insert( std::move( x ), root, parent );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */

    void remove( const Comparable x )
    {
        remove( x, root );
    }

    const Comparable get_parent( const Comparable &x )
    {
        shared_ptr<BinaryNode> current = _find(x, root);
        if( current != nullptr && current->parent.lock() != nullptr ){
                return current->parent.lock()->element;
        }
        else return Comparable();


    }

  private:

    shared_ptr<BinaryNode> root;
    int counter = 0;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable &x, shared_ptr<BinaryNode> &current, weak_ptr<BinaryNode> &parent)
    {

        if( current == nullptr ){
            //cout << "Inserting new node" << endl;
            current = make_shared<BinaryNode>(x, nullptr, nullptr, parent);

        }

        else if( x < current->element ){
            //cout << "Moving left" << endl;
            parent = current;
            insert( x, current->left, parent );
            //cout << "Current = " << current->element << " Parent = " << parent.lock()->element << endl;
        }

        else if( current->element < x ){
            //cout << "Moving right" << endl;
            parent = current;
            insert( x, current->right, parent );
            //cout << "Current = " << current->element << " Parent = " << parent.lock()->element << endl;
        }
        else
        {
            ;  // Duplicate; do nothing
        }
    }



    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable &&x, shared_ptr<BinaryNode> current,  weak_ptr<BinaryNode> &parent )
    {
        if( current == nullptr )
            current = make_shared<BinaryNode>( std::move( x ), nullptr, nullptr, parent);
        else if( x < current->element ){
            parent = current;
            insert( std::move( x ), current->left, parent);
        }
        else if( current->element < x ){
            parent = current;
            insert( std::move( x ), current->right, parent);
        }
        else
        {
             ;  // Duplicate; do nothing
        }
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, shared_ptr<BinaryNode> &t ){

        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            shared_ptr<BinaryNode> oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;

        }

    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    shared_ptr<BinaryNode> findMin(shared_ptr<BinaryNode> t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    shared_ptr<BinaryNode> findMax( shared_ptr<BinaryNode> t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, shared_ptr<BinaryNode> t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */


    shared_ptr<BinaryNode> _find( const Comparable & x, shared_ptr<BinaryNode> t ) const {
        if( t == nullptr)
            return nullptr;
        else if( x < t->element){
            return _find(x, t->left);
        }
        else if( x > t->element){
            return _find(x, t->right);
        }
        else return t; //match
    }


    void makeEmpty( shared_ptr<BinaryNode> &t )
    {
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void printTree( shared_ptr<BinaryNode> t, ostream & out ) const
    {
        preorder_print( t, out, counter );
    }

     void preorder_print( shared_ptr<BinaryNode> t, ostream & out, int indention ) const{
        if(t != nullptr){
            out << setw(indention) << t->element << endl;
            preorder_print(t->left, out, indention + 4);
            preorder_print(t->right, out, indention+ 4);
        }
     }

    /**
     * Internal method to clone subtree.
     */
    shared_ptr<BinaryNode> clone( shared_ptr<BinaryNode> t, const shared_ptr<BinaryNode>& parent ) const
    {
        if( t == nullptr )
            return nullptr;
        else{
            auto current = make_shared<BinaryNode>( t->element, nullptr, nullptr, parent );
            current->left = clone(t->left, current);
            current->right = clone(t->right, current);
            return current;
        }
    }

    /* Tree
             20
          /     \
         10      30
        /  \    /  \
       5   15  25   35
           /        /
          12       33
           \
           14          */


    shared_ptr<BinaryNode> find_succes(shared_ptr<BinaryNode>& current){
        if(current && current->right){
            return findMin(current->right);
        }
        else {
            return findMin(current->parent.lock()->left);
        }

    }

    shared_ptr<BinaryNode> find_pre(shared_ptr<BinaryNode>& current){
        if(current && current->left ){
            return findMax(current->left);
        }
        else {
            return findMax(current->parent.lock()->right);
        }

    }
/*
   void find_pre_success(shared_ptr<BinaryNode> current, Comparable& x, Comparable& low, Comparable& high) {

        if(current = nullptr)
            return;
        else if(current->element == x){
            if(current->left != nullptr){
                current = current->left;
                find_pre_success(current->right, x, low, high);
            }
            if(current->right != nullptr){
                current = current->right;
                find_pre_success(current->left, x, low, high);
            }

        }

        /*
        if(current == nullptr){
            return;
        }
        //left in tree
        else if(x < current->element) {
            high = current->element;
            if(current->left->element < x) {
                low = current->left->element;
                find_pre_success(current->left, x, low, high);
        }
            else{
                find_pre_success(current->left, x, low, high);
            }
        }
        else if(x > current->element) {
            low = current->element;
            if(current->right->element > x) {
                high = current->right->element;
                find_pre_success(current->right, x, low, high);
            }
            else {
                find_pre_success(current->right, x, low, high);
            }
        }

    }
    */
};

#endif
