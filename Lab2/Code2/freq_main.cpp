#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <utility>
#include "BinarySearchTree.h"

using namespace std;

class thepair {
public:
    string word;
    int counter;

    //thepair():word{NULL}, freq(0) {}
    thepair(string s, int c) : word{s}, counter{c} {}

    void setPair(string s){
        word = s;
        counter = 1;
    }

    bool operator<(const thepair & p) const
    {
        return word < p.word;
    }
};

ostream &operator<<(ostream& out, const thepair thePair) {
    out << right << setw(14) << thePair.word << " " << thePair.counter;
    return out;
}



int main( )
{
    BinarySearchTree<thepair> theTree;
    //thepair p;

    ifstream file("words.txt");

    if (!file)
    {
        cout << "couldn't open file words.txt" << endl;
        return 1;
    }

    vector<string> V1 = { istream_iterator<string>{file}, istream_iterator<string>{} };
    file.close();

    for(auto j: V1)
    {
        thepair p(j, 1);
        auto temp = theTree.contains(p);

        if(temp != theTree.end() ){
            temp->counter++;
        }
        else {
            theTree.insert(p);
        }
    }

    for(auto p : theTree) {
        cout << p << endl;
    }

    cout << "Exiting" << endl;
    return 0;
}
