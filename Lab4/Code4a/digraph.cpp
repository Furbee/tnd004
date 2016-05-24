/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    // Assess input
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    //input ok. Do:

    init_list(s);

    int v = 0;
    Queue<int> Q;
    Q.enqueue(s);

    //Do while there's stuff in the queues
    while (!Q.isEmpty()) {
        v = Q.getFront();
        Q.dequeue();

        Node* adjacent = array[v].getFirst();

        //for all adjacent vectors check if it's been visited. If has not, set path and dist.
         while( adjacent ){
            if ( dist[adjacent->vertex] == INFINITY )
            {
                dist[adjacent->vertex] = dist[v] + 1;   //the distance from the origin
                path[adjacent->vertex] = v;             //the path goes from v
                Q.enqueue(adjacent->vertex);            //enqueue the vector
            }
             adjacent = array[v].getNext(); //check next adjacent vector
        }
    }
}


// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    //input ok. Do:
    init_list(s);

    //Do while there's stuff in the queues
    while ( true ) {

        Node* adjacent = array[s].getFirst();

        while( adjacent ) {
            if ( !done[adjacent->vertex] && dist[adjacent->vertex] > dist[s] + adjacent->weight )
            {
                dist[adjacent->vertex] = dist[s] + adjacent->weight;    //the distance from the origin
                path[adjacent->vertex] = s;                             //the path goes from v
            }
            adjacent = array[s].getNext(); //check next adjacent vector
        }
            done[s] = true;

            int smallest = INFINITY;


            for( int i = 1 ; i <= size ; i++ ){
                if( dist[i] < smallest && !done[i] ){
                    smallest = dist[i];
                    s = i;
                }
            }

            //v = smallest_distance();

            if( smallest == INFINITY ) break;


    }
}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }

    vector<int> v;
    vector<int>::reverse_iterator iter;

    int distance = dist[t];

    while(path[t] != 0)
    {
        v.push_back(t); // Adds a new element at the end of the vector, after its current last element.
        t = path[t];
    }
    v.push_back(t);

    for(iter = v.rbegin(); iter != v.rend(); iter++)
    {
        std::cout << *iter << "  ";
    }

    std::cout << " ( " << distance << " ) " << endl;

}

/**
 *  Internal method for initialize a list.
 *  Origin is the given source
 */

void Digraph::init_list(int origin){
    for(int i = 1; i <= size; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = false;
    }
    dist[origin] = 0;
    done[origin] = true;

}
