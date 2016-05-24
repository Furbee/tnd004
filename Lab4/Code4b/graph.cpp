/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n) {
    assert(n >= 1);
    array = new List[n + 1];
    size = n;
}

// -- DESTRUCTOR

Graph::~Graph() {
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const {

    vector<Edge> edge;

    //allocate memory for values needed
    //can do without any of these..?
    int *dist = new int[size + 1];
    int *path = new int[size + 1];
    bool *done = new bool[size + 1];

    // init values of the list
    for(int i = 1; i <= size; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = false;
    }

    int s = 1, totalWeight = 0;; // s = start position
    dist[s] = 0;
    done[s] = true;

    // set shortest paths for the graph
    while (true)
    {
        Node *adjacent = array[s].getFirst();

        while (adjacent)
        {
            if (!done[adjacent->vertex] && dist[adjacent->vertex] > adjacent->weight)
            {
                dist[adjacent->vertex] = adjacent->weight;              //the distance from the origin
                path[adjacent->vertex] = s;                             //the path goes from v
            }
            adjacent = array[s].getNext(); //check next adjacent vector
        }

        done[s] = true;

        edge.push_back(Edge(s, path[s], dist[s]));

        int smallest = INFINITY;

        // look for smallest distance vertex
        for (unsigned int i = 1; i <= size ; i++)
        {
            if (!done[i] && dist[i] < smallest )
            {
                smallest = dist[i];
                s = i;
            }
        }

        if (smallest == INFINITY) break;
    }

    // calculate total weight
    for (unsigned int i = 1 ; i < edge.size() ; ++i)
    {
        std::cout << "( " << edge[i].tail << ", " << edge[i].head << ". " << edge[i].weight << ")" << endl;
        totalWeight += edge[i].weight;
    }

    std::cout <<"Total weight: " << totalWeight << endl
              << "=====================================================================" << endl;

    //deallocate memory
    delete[] dist;
    delete[] path;
    delete[] done;
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const {

    //TODO:

    Heap<Edge> H;
    DSets D(size);

    int total = 0, counter = 0;

    //H.heapify(H);
    for (int i = 1 ; i <= size ; i++)
    {
        Node *current = array[i].getFirst();
        while (current)
        {
            if (current->vertex < i)
            {
                H.insert( Edge(current->vertex, i, current->weight) );
            }
            current = array[i].getNext();
        }
    }
    //Heapification done

    //find new edges
    while (counter < size-1) //number of edges must be n-1
    {
        Edge n = H.deleteMin();
        if ( D.find(n.head) != D.find(n.tail) )
        {
            D.join( D.find(n.head), D.find(n.tail) );
            counter++;
            total += n.weight;
            cout << n << endl;
        }

    }
    cout << endl << "Total weight of this mf masterpiece is somewhere around exactly: " << total << endl
         << "=====================================================================" << endl;
}

// print graph
void Graph::printGraph() const {
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++) {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

