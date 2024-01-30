#include <iostream>

using namespace std;

int main(void)
{
    cout << "=======================" << endl;


    /**
     * Declaration, Assignment
     */
    bool b0 = 0 == 0;
    bool b1 = 0 < 1;
    bool b2 = 0 > 1;

    cout << "b0(0 == 0): " << b0 << endl;
    cout << "b1(0 < 1):  " << b1 << endl;
    cout << "b2(0 > 1):  " << b2 << endl;


    cout << "-----------------------" << endl;


    /**
     * https://en.cppreference.com/w/cpp/header/iostream <ios> class ios_base
     */
    cout.setf(ios_base::boolalpha);
    cout << "cout.setf(ios_base::boolalpha);" << endl;
    cout << "b0: " << b0 << endl;
    cout << "b1: " << b1 << endl;
    cout << "b2: " << b2 << endl;


    cout << "=======================" << endl;

    /**
     * relation with integer
     */
    int itrue = true;
    int ifalse = false;

    cout << "int itrue = true; :   " << itrue << endl;
    cout << "int ifalse = false; : " << ifalse << endl;

    cout << "-----------------------" << endl;

    bool btrue = 100;
    bool bfalse = 0;

    cout << "bool btrue = true; :   " << btrue << endl;
    cout << "bool bfalse = false; : " << bfalse << endl;


    cout << "=======================" << endl;

    return 0;
}