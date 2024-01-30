#include <iostream>
#include <limits>

using namespace std;

int main(void)
{
    cout << "=======================" << endl;


    /**
    * TERNARY: Expression(condition) ? Expression(true) : Expression(false)
    */

    int int_num = -10;
    int abs = int_num < 0 ? -int_num : int_num;

    cout << "abs(-10): " << abs << endl;

    cout << "-----------------------" << endl;

    int_num = 0;
    (int_num == 0 ? (cout << "int_num == 0") : (cout << "int_num != 0")) << endl;
    cout << (int_num == 0 ? "int_num == 0" : "int_num != 0") << endl;

    cout << "-----------------------" << endl;
    
    int_num = 0;
    cout << sizeof(int_num) << endl;
    cout << sizeof int_num << endl;
    cout << sizeof(int) << endl;

    cout << "-----------------------" << endl;

    /**
     * SCOPERESOLUTION: '::'
     */

    std::cout << 1 << std::endl;
    std::ios_base::floatfield;

    cout << "-----------------------" << endl;

    /**
     * IMPLICIT CASTING vs EXPLICIT CASTING
     */

    // static_cast
    // const_cast
    // dynamic_cast
    // reinterpret_cast

    unsigned int uint_num = 1;
    float float_num = 1.1f;
    int_num = 1u;

    uint_num = int_num;
    int_num = uint_num;
    float_num = int_num;

    /**
     * 0111,1111,1111,1111,1111,1111,1111,1111: int max
     * 1111,1111,1111,1111: casting to short from left
     * 0000,0000,0000,0000: 1's complement
     * 0000,0000,0000,0001: 2's complement -> -1
     */
    short short_num = numeric_limits<int>::max();
    cout << short_num << endl;

    cout << 'a' << endl;
    cout << (int)'a' << endl;
    cout << int('a') << endl;


    cout << "=======================" << endl;

    return 0;
}