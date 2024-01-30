#include <iostream>

/**
 * Defines the class template numeric_limits and two enumerations concerning floating-point representations and rounding.
 */
#include <limits>

using namespace std;

int main(void)
{
    cout << "=======================" << endl;


    /**
     * Declaration, Assignment
     */
    int x;
    x = 0;
    cout << "int x; x = 0; : " << x << endl;

    /**
     * C Style
     */
    int y = 1;
    cout << "int y = 1; : " << y << endl;

    /**
     * C++ Style
     */
    int z(2);
    cout << "int z(2); : " << z << endl;


    cout << "=======================" << endl;


    /**
     * Integer Literal
     */
    int il0 = 11;
    int il1 = 0b11;
    int il2 = 011;
    int il3 = 0x11;

    cout << "il0 decimal: " << il0 << endl;
    cout << "il1 binary:  " << il1 << endl; 
    cout << "il2 octal:   " << il2 << endl;
    cout << "il3 hexa:    " << il3 << endl;


    cout << "=======================" << endl;


    /**
     * sizeof operator
     */
    int int_num = 0;
    long long_num = 0;
    int *int_ptr = &int_num;

    cout << "sizeof(int):     " << sizeof(int_num) << endl;
    cout << "sizeof(long):    " << sizeof(long_num) << endl;
    cout << "sizeof(int *):   " << sizeof(int_ptr) << endl;

    int8_t int8_num = 0;
    int16_t int16_num = 0;
    int32_t int32_num = 0;

    cout << "sizeof(int8_t):  " << sizeof(int8_num) << endl;
    cout << "sizeof(int16_t): " << sizeof(int16_num) << endl;
    cout << "sizeof(int32_t): " << sizeof(int32_num) << endl;


    cout << "=======================" << endl;


    /**
     * Assignment with type
     */
    int int_type = 11;
    unsigned int uint_type = 11u;
    long int long_type = 0L;
    long long long_long_type = 0LL;
    unsigned long long ulong_long_type = 0uLL;


    /**
     * https://en.cppreference.com/w/cpp/types/numeric_limits
     */
    cout << "numeric_limits<uint> max()" << endl;
    cout << "-----------------------" << endl;
    cout << "uint8_t:  " << (int)numeric_limits<uint8_t>::max() << endl;
    cout << "uint16_t: " << numeric_limits<uint16_t>::max() << endl;
    cout << "uint32_t: " << numeric_limits<uint32_t>::max() << endl;
    cout << "uint64_t: " << numeric_limits<uint64_t>::max() << endl;


    cout << "=======================" << endl;


    cout << "numeric_limits<int> max()" << endl;
    cout << "-----------------------" << endl;
    cout << "int8_t:  " << (int)numeric_limits<int8_t>::max() << endl;
    cout << "int16_t: " << numeric_limits<int16_t>::max() << endl;
    cout << "int32_t: " << numeric_limits<int32_t>::max() << endl;
    cout << "int64_t: " << numeric_limits<int64_t>::max() << endl;


    cout << "=======================" << endl;


    cout << "numeric_limits<int> min()" << endl;
    cout << "-----------------------" << endl;
    cout << "int8_t:  " << (int)numeric_limits<int8_t>::min() << endl;
    cout << "int16_t: " << numeric_limits<int16_t>::min() << endl;
    cout << "int32_t: " << numeric_limits<int32_t>::min() << endl;
    cout << "int64_t: " << numeric_limits<int64_t>::min() << endl;


    cout << "=======================" << endl;


    /**
     * Overflow, Underflow
     */
    uint32_t uint32_pnum = numeric_limits<uint32_t>::max();
    uint32_t uint32_onum = uint32_pnum + 1;

    cout << "uint32 max:      " << uint32_pnum << endl;
    cout << "uint32 overflow: " << uint32_onum << endl;

    int32_t int32_pnum = numeric_limits<int32_t>::max();
    int32_t int32_onum = int32_pnum + 1;

    cout << "int32 max:      " << int32_pnum << endl;
    cout << "int32 overflow: " << int32_onum << endl;

    uint32_pnum = numeric_limits<uint32_t>::min();
    uint32_onum = uint32_pnum - 1;

    cout << "uint32 min:       " << uint32_pnum << endl;
    cout << "uint32 underflow: " << uint32_onum << endl;

    int32_pnum = numeric_limits<int32_t>::min();
    int32_onum = int32_pnum - 1;

    cout << "int32 min:       " << int32_pnum << endl;
    cout << "int32 underflow: " << int32_onum << endl;


    cout << "=======================" << endl;

    return 0;
}
