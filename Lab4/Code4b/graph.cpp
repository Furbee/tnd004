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

    int *dist = new int[size + 1];
    int *path = new int[size + 1];
    bool *done = new bool[size + 1];

    int s = 1; //Start position
    vector<Edge> edge;


    //Do while there's stuff in the queues
    while (true) {

        Node *adjacent = array[s].getNext();

        while (adjacent) {
            if (!done[adjacent->vertex] && dist[adjacent->vertex] > adjacent->weight) {
                dist[adjacent->vertex] = adjacent->weight;    //the distance from the origin
                path[adjacent->vertex] = s;                             //the path goes from v
            }
            adjacent = array[s].getNext(); //check next adjacent vector
        }
        done[s] = true;

        int smallest = INFINITY;


        for (int i = 1; i <= size; i++) {
            if (dist[i] < smallest && !done[i]) {
                smallest = dist[i];
                s = i;
            }
        }

        if (smallest == INFINITY) break;
    }

    int weight = 0;

    for (unsigned int i = 1; i < edge.size(); ++i)
    {
        std::cout << "( " << edge[i].tail << ", " << edge[i].head << ". " << edge[i].weight << ")" << endl;
        weight += edge[i].weight;
    }

    std::cout << endl <<"Total weight = " << weight;

    delete[] dist;
    delete[] path;
    delete[] done;
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const {

    //TODO:
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