#include <iostream>

/**
 * g++ -o ch04_02_comparison_relational ch04_02_comparison_relational.cpp -std=c++20
 * such as the spaceship operator (<=>), 
 * you'll need to ensure that your compiler supports C++20 and use the appropriate compiler flag to enable it.
 */
#include <compare>

using namespace std;

int main(void)
{
    cout << "=======================" << endl;

    /**
     * equal to(==) VS assignment(=)
     */
    int num0 = 10, num1(10);

    if (num0 == num1) 
        cout << "num0 == num1: true" << endl;
    else
        cout << "num0 == num1: false" << endl;

    cout << num0 << ", " << num1 << endl;

    cout << "-----------------------" << endl;

    num0 = 10, num1 = 11;

    if (num0 = num1)
        cout << "num0(10) = num1(11): true" << endl;
    else
        cout << "num0(10) = num1(11): false" << endl;

    cout << num0 << ", " << num1 << endl;

    cout << "-----------------------" << endl;

    num0 = 0, num1 = 0;

    if (num0 = num1)
        cout << "num0(0) = num1(0): true" << endl;
    else
        cout << "num0(0) = num1(0): false" << endl;

    cout << num0 << ", " << num1 << endl;

    cout << "-----------------------" << endl;

    num0 = 0, num1 = 0;

    if (num0 != num1)
        cout << "num0(0) != num1(0): true" << endl;
    else
        cout << "num0(0) != num1(0): false" << endl;

    cout << num0 << ", " << num1 << endl;

    cout << "-----------------------" << endl;

    num0 = 0, num1 = 1;

    if (num0 != num1)
        cout << "num0(0) != num1(1): true" << endl;
    else
        cout << "num0(0) != num1(1): false" << endl;

    cout << num0 << ", " << num1 << endl;

    cout << "-----------------------" << endl;

    num0 = 0, num1 = 0;

    if (num0 > num1)
        cout << "num0(0) > num1(0): true" << endl;
    else
        cout << "num0(0) > num1(0): false" << endl;

    cout << num0 << ", " << num1 << endl;

    cout << "-----------------------" << endl;

    num0 = 1, num1 = 0;
    if (num0 > num1)
        cout << "num0(1) > num1(0): true" << endl;
    else
        cout << "num0(1) > num1(0): false" << endl;

    cout << num0 << ", " << num1 << endl;

    cout << "-----------------------" << endl;

    num0 = 0, num1 = 0;

    if (num0 >= num1)
        cout << "num0(0) >= num1(0): true" << endl;
    else
        cout << "num0(0) >= num1(0): false" << endl;

    cout << num0 << ", " << num1 << endl;

    cout << "-----------------------" << endl;

    num0 = 1, num1 = 0;

    if (num0 >= num1)
        cout << "num0(1) >= num1(0): true" << endl;
    else
        cout << "num0(1) >= num1(0): false" << endl;

    cout << num0 << ", " << num1 << endl;

    cout << "-----------------------" << endl;

    num0 = 0, num1 = 0;

    if (num0 < num1)
        cout << "num0(0) < num1(0): true" << endl;
    else
        cout << "num0(0) < num1(0): false" << endl;

    cout << num0 << ", " << num1 << endl;

    cout << "-----------------------" << endl;

    num0 = 0, num1 = 1;

    if (num0 < num1)
        cout << "num0(0) < num1(1): true" << endl;
    else
        cout << "num0(0) < num1(1): false" << endl;

    cout << num0 << ", " << num1 << endl;

    cout << "-----------------------" << endl;
    
    num0 = 0, num1 = 0;

    if (num0 <= num1)
        cout << "num0(0) <= num1(0): true" << endl;
    else
        cout << "num0(0) <= num1(0): false" << endl;

    cout << num0 << ", " << num1 << endl;

    cout << "-----------------------" << endl;

    num0 = 0, num1 = 1;

    if (num0 <= num1)
        cout << "num0(1) <= num1(0): true" << endl;
    else
        cout << "num0(1) <= num1(0): false" << endl;

    cout << num0 << ", " << num1 << endl;

    cout << "-----------------------" << endl;

    cout.setf(ios_base::boolalpha);

    cout << ((1 <=> 1) == 0) << endl;
    cout << ((2 <=> 1) > 0) << endl;
    cout << ((1 <=> 2) < 0) << endl;
    cout << is_eq(1 <=> 1) << endl;
    cout << is_gt(2 <=> 1) << endl;
    cout << is_lt(1 <=> 2) << endl;

    cout << is_gteq(2 <=> 1) << endl;
    cout << is_lteq(1 <=> 2) << endl;

    /**
     * equal to VS equivalent
     */
    cout << typeid(1 <=> 1).name() << endl;
    cout << typeid(1 <=> 1.0).name() << endl;


    cout << "=======================" << endl;

    return 0;
}