#include <iostream>
#include <iomanip>

#include "set.h"

using namespace std;

//Your code for class Set should pass the tests in this file
//before your HA session on week 47
//Expected output is in the file out_uppg2_test.txt

int main()
{

    int A1[] = { 1, 3, 5 };
    int A2[] = { 4, 3, 2 };  //not sorted!!

    /*****************************************************
    * TEST PHASE 0                                       *
    * Constructors                                       *
    ******************************************************/
    cout << "\nTEST PHASE 0: constructors\n" << endl;

    Set S1(A1, 3);
    Set S2(A2, 3);
    //Set S2 { 4, 3, 2 };

    Set S3; //default constructor
    Set S4; //default constructor


    cout << "S1 = " << S1 << endl;
    cout << "S2 = " << S2 << endl;
    cout << "S3 = " << S3 << endl;
    cout << "S4 = " << S4 << endl;

    /*****************************************************
    * TEST PHASE 1                                       *
    * Copy constructor                                   *
    ******************************************************/
    cout << "\nTEST PHASE 1: copy constructor\n" << endl;

    Set S5(S1);  //copy constructor

    cout << "S5 = " << S5 << endl;

    /*****************************************************
    * TEST PHASE 2                                       *
    * Assignment operator                                *
    ******************************************************/
    cout << "\nTEST PHASE 2: assignment\n" << endl;

    S3 = S4 = S5;

    cout << "S3 = " << S3 << endl;
    cout << "S4 = " << S4 << endl;

    /*****************************************************
    * TEST PHASE 3                                       *
    * Member functions: member and cardinality           *
    ******************************************************/
    cout << "\nTEST PHASE 3: member functions\n" << endl;

    for (int i = 1; i <= 5; i++)
    {
        cout << "S3.member(" << i << ") ? " << (S3.member(i) ? 'T' : 'F') << endl;
    }
    cout << "\nS3.member(99999) ? " << (S3.member(99999) ? 'T' : 'F') << endl;
    cout << "\nS3.cardinality() = " << S3.cardinality() << endl;

    /*******************************************************
    * TEST PHASE 4                                         *
    * Operator overloading:operator+                       *
    ********************************************************/
    cout << "\nTEST PHASE 4: union\n" << endl;

    S3 = S1 + S2;

    cout << "S3 = " << S3 << endl;

    return 0;
}
