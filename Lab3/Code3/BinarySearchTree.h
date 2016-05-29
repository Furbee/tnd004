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

/*
        Tree
         20
      /     \
     10      30
    /  \    /  \
   5   15  25   35
       /        /
      12       33
       \
       14
*/

template<typename Comparable>
class BinarySearchTree
{
public:

    class BiIterator;

    BinarySearchTree() : root {nullptr}
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root {nullptr}
    {
        root = clone(rhs.root, nullptr);
    }

    /**
     * Move constructor
     */
    BinarySearchTree(BinarySearchTree &&rhs) : root {rhs.root}
    {
        rhs.root = nullptr;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree()
    {
        makeEmpty();
    }

    /**
     * Copy assignment
     */
    BinarySearchTree &operator=(const BinarySearchTree &rhs)
    {
        BinarySearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    /**
     * Move assignment
     */
    BinarySearchTree &operator=(BinarySearchTree &&rhs)
    {
        std::swap(root, rhs.root);
        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const
    {
        if (isEmpty())
            throw UnderflowException {};
        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const
    {
        if (isEmpty())
            throw UnderflowException {};
        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
//    bool contains(const Comparable &x) const
//    {
//        return contains(x, root);
//    }
    BiIterator contains(const Comparable &x) const
    {
        return contains(x, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree(ostream &out = cout) const
    {
        if (isEmpty())
            out << "Empty tree" << endl;
        else
            printTree(root, out);
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable x)
    {
        weak_ptr<BinaryNode> parent = root;
        insert(x, root, parent);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(Comparable &&x)
    {
        weak_ptr<BinaryNode> parent = root;
        insert(std::move(x), root, parent);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */

    void remove(const Comparable x)
    {
        remove(x, root);
    }

    const Comparable get_parent(const Comparable &x)
    {
        shared_ptr<BinaryNode> current = _find(x, root);
        if (current != nullptr && current->parent.lock() != nullptr)
        {
            return current->parent.lock()->element;
        }
        else return Comparable();
    }

    void find_pred_succ(Comparable x, Comparable &low, Comparable &high)
    {
        //call private help function
        find_pre_success(x, low, high, root);
    }

    /**
         * Method returns pointer to beginning of the tree
         * That is the min value.
         */
    BiIterator begin()
    {
        return BiIterator( findMin( root ) );
    }
    BiIterator end()
    {
        return BiIterator();//{ make_shared<BinaryNode>(Comparable{},strongPtr{},strongPtr{}, weakPtr{} ), this};
    }


private:
    /*******************************************************************
     *                      BINARY NODE
     *******************************************************************/

    struct BinaryNode
    {

        Comparable element;

        shared_ptr<BinaryNode> left, right;
        weak_ptr<BinaryNode> parent;

        BinaryNode(const Comparable &theElement, shared_ptr<BinaryNode> lt, shared_ptr<BinaryNode> rt,
                   weak_ptr<BinaryNode> pt)
            : element {theElement}, left {lt}, right {rt}, parent {pt} { }

        BinaryNode(Comparable &&theElement, shared_ptr<BinaryNode> lt, shared_ptr<BinaryNode> rt,
                   weak_ptr<BinaryNode> pt)
            : element {std::move(theElement)}, left {lt}, right {rt}, parent {pt} { }
    };

private:
    // private variables
    shared_ptr<BinaryNode> root;

    /*******************************************************************
     *                      BiIterator Class
     *******************************************************************/

public:
    class BiIterator
    {
    private:

        shared_ptr<BinaryNode> current;

    public:
        BiIterator() : current(nullptr)
        {
            //current = nullptr;
            //bst = nullptr;
        };

        BiIterator( shared_ptr<BinaryNode> t ) : current {t} {};

        Comparable& operator*() const
        {
            return current->element;
        }

        //TODO: Ask about shared_ptr vs *
        Comparable* operator->() const
        {
            if (current) {
                return &(current->element);
            }
            return nullptr;
        }

        bool operator==(const BiIterator &it) const
        {
            return this->current == it.current;
        }

        bool operator!=(const BiIterator &it) const
        {
            return this->current != it.current;

        }
        // pre-increment
        BiIterator &operator++()
        {
            current = find_success(current);
            return *this;
        }
        //post-increment
         BiIterator &operator++(int)
        {
            BiIterator tmp(*this);
            operator++(); // pre-increment this instance
            return tmp;   // return value before increment
        }
        // pre
        BiIterator &operator--()
        {
            current = find_pred(current);
            return *this;
        }
        // post
        BiIterator &operator--(int)
        {
            BiIterator tmp(*this);
            operator--(); // pre-decrement this instance
            return tmp;   // return value before decrement
        }

    private:
        /**
        *   Internal methods to find the
        *    successor of a current node
        **/
        shared_ptr<BinaryNode> find_success( shared_ptr<BinaryNode>& currento)
        {
            if(currento && currento->right) // put first check (if currento) over the whole function to avoid reaching outside. if not then return nullptr.
            {
                return( findMin(currento->right) );
            }
            else
            {
                auto parento = currento->parent.lock();
                while(parento != nullptr && currento == parento->right)
                {
                    currento = parento;
                    parento = parento->parent.lock();
                }
                return parento;
            }
            return nullptr;
        }


        /**
        *   Internal methods to find the
        *    predecessor of a current node
        **/
        shared_ptr<BinaryNode> find_pred( shared_ptr<BinaryNode>& currento )
        {
            if(currento && currento->left) // put first check (if currento) over the whole function to avoid reaching outside. if not then return nullptr.
            {
                return findMax( currento->left );
            }
            else
            {
                auto parento = current->parent.lock();
                while( parento != nullptr && currento == parento->left )
                {
                    currento = parento;
                    parento = parento->parent.lock();
                }
                return parento;
            }
        }
    };


    /*******************************************************************
     *                      INTERNAL METHODS
     *******************************************************************/

private:
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable &x, shared_ptr<BinaryNode> &current, weak_ptr<BinaryNode> &parent)
    {

        if (current == nullptr)
        {
            //cout << "Inserting new node" << endl;
            current = make_shared<BinaryNode>(x, nullptr, nullptr, parent);
            //cout << setw(14) << left << x << " inserted." << endl;

        }

        else if (x < current->element)
        {
            //cout << "Moving left" << endl;
            parent = current;
            insert(x, current->left, parent);
            //cout << "Current = " << current->element << " Parent = " << parent.lock()->element << endl;
        }

        else if (current->element < x)
        {
            //cout << "Moving right" << endl;
            parent = current;
            insert(x, current->right, parent);
            //cout << "Current = " << current->element << " Parent = " << parent.lock()->element << endl;
        }
        else
        {
            //cout << setw(14) << left <<  x << " is a duplicate." << endl;
            ;  // Duplicate; do nothing
        }
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(Comparable &&x, shared_ptr<BinaryNode> current, weak_ptr<BinaryNode> &parent)
    {
        if (current == nullptr)
            current = make_shared<BinaryNode>(std::move(x), nullptr, nullptr, parent);
        else if (x < current->element)
        {
            parent = current;
            insert(std::move(x), current->left, parent);
        }
        else if (current->element < x)
        {
            parent = current;
            insert(std::move(x), current->right, parent);
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
    void remove(const Comparable &x, shared_ptr<BinaryNode> &t)
    {

        if (t == nullptr)
            return;   // Item not found; do nothing
        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) // Two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            shared_ptr<BinaryNode> oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;

        }

    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    static shared_ptr<BinaryNode> findMin(shared_ptr<BinaryNode> t)
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    static shared_ptr<BinaryNode> findMax(shared_ptr<BinaryNode> t)
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
//    bool contains(const Comparable &x, shared_ptr<BinaryNode> t) const
//    {
//        if (t == nullptr)
//            return false;
//        else if (x < t->element)
//            return contains(x, t->left);
//        else if (t->element < x)
//            return contains(x, t->right);
//        else
//            return true;    // Match
//    }

    BiIterator contains(const Comparable &x, shared_ptr<BinaryNode> t) const
    {
        if (t == nullptr)
        {
            //not found
            return BiIterator();
        }
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
        {
           return BiIterator(t);    // Match
        }
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


    shared_ptr<BinaryNode> _find(const Comparable &x, shared_ptr<BinaryNode> t) const
    {
        if (t == nullptr)
            return nullptr;
        else if (x < t->element)
        {
            return _find(x, t->left);
        }
        else if (x > t->element)
        {
            return _find(x, t->right);
        }
        else return t; //match
    }


    void makeEmpty(shared_ptr<BinaryNode> &t)
    {
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void printTree(shared_ptr<BinaryNode> t, ostream &out) const
    {
        preorder_print(t, out, 0);
    }

    /**
     * Internal method to print a subtree rooted at t
     * Uses preorder print
     */

    void preorder_print(shared_ptr<BinaryNode> t, ostream &out, int indention) const
    {
        if (t != nullptr)
        {
            out << setw(indention) << t->element << endl;
            preorder_print(t->left, out, indention + 4);
            preorder_print(t->right, out, indention + 4);
        }
    }

    /**
     * Internal method to clone subtree.
     */
    shared_ptr<BinaryNode> clone(shared_ptr<BinaryNode> t, const shared_ptr<BinaryNode> &parent) const
    {
        if (t == nullptr)
            return nullptr;
        else
        {
            auto current = make_shared<BinaryNode>(t->element, nullptr, nullptr, parent);
            current->left = clone(t->left, current);
            current->right = clone(t->right, current);
            return current;
        }
    }

    /**
    * Internal method to find and set value of the
    * Predecessor and Successor of a given BST
    *
    * Predecessor = Floor
    * Successor = Ceiling
    */

    void find_pre_success(const Comparable &key, Comparable &floor, Comparable &ceiling, const shared_ptr<BinaryNode> current)
    {

        //base case -> stop recursion when:
        if (current == nullptr) return;

        // if key is found:
        if (key == current->element)
        {

            // floor will be max value of left tree,
            if (current->left != nullptr)
                floor = findMax(current->left)->element;


            // ceiling will be min value of right tree
            if (current->right != nullptr)
                ceiling = findMin(current->right)->element;

            return;
        }

        // key larger than current element: set floor to current element and go right
        else if (key > current->element)
        {
            floor = current->element;
            find_pre_success(key, floor, ceiling, current->right);
        }

        // key smaller than current element: set ceiling to current element and go left
        else if (key < current->element)
        {
            ceiling = current->element;
            find_pre_success(key, floor, ceiling, current->left);
        }
    }
};


#endif
