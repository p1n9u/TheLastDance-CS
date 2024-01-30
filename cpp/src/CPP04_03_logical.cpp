#include <iostream>

using namespace std;

int main(void)
{
    cout << "=======================" << endl;


    int num0 = 10, num1 = 10;
    int num2 = 20, num3 = 30;

    /**
     * true && true
     * true && false
     */
    if (num0 == num1 && num2 != num3) 
        cout << "!!!!" << endl;
    if (num0 == num1 && num2 == num3)
        cout << "@@@@" << endl;

    cout << "-----------------------" << endl;

    num0 = 10, num1 = 10;
    num2 = 20, num3 = 30;

    /**
     * true && false
     * true ||
     */
    if (num0 == num1 && num2 == num3)
        cout << "AND" << endl;
    if (num0 == num1 || num2 == num3)
        cout << "OR" << endl;

    cout << "-----------------------" << endl;

    /**
     * Order of operations
     * true || true
     */
    if (true || false && false)
        cout << "OK" << endl;

    cout << "-----------------------" << endl;

    num0 = 10, num1 = 20;
    num2 = 20, num3 = 20;

    /** 
     * short-circuit evaluation
     * false && 
     * true ||
     */
    if (num0 == num1 && num2 == num3)
        cout << "AND" << endl;
    if (num0 != num1 || num2 == num3)
        cout << "OR" << endl;

    cout << "-----------------------" << endl;

    false && printf("ABC");
    cout << endl;

    printf("a") && printf("ABC");
    cout << endl;

    printf("a") || printf("ABC");
    cout << endl;

    false || printf("ABC");
    cout << endl;

    cout << "-----------------------" << endl;

    bool r = true;
    r = !r;
    cout << r << endl;

    num0 = 10, num1 = 20;

    if (num0 != num1)
        cout << "num0 != num1" << endl;

    if (!(num0 == num1))
        cout << "!(num0 == num1)" << endl;

    cout.setf(ios_base::boolalpha);

    cout << !10 << endl;

    cout << (1 && 2) << endl;


    cout << "=======================" << endl;

    return 0;
}