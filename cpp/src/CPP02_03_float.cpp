#include <iostream>

/**
 * Includes the Standard C library header.
 */
#include <cmath>
#include <cfloat>
#include <cstring>

using namespace std;

/**
 * https://codetorial.net/articles/floating_point.html
 */
int main(void)
{
    cout << "=======================" << endl;


    /**
     * Declaration, Assignment
     */
    float num0 = 1.5;
    float num1 = num0 * 1.5;
    float num2 = num0 / 2;
    float num3 = num0 - 3;

    cout << "num0: " << num0 << endl;
    cout << "num1: " << num1 << endl;
    cout << "num2: " << num2 << endl;
    cout << "num3: " << num3 << endl;


    cout << "=======================" << endl;


    /**
     * sizeof operator
     */
    float fnum = 1.0f;
    double dnum = 1.0;
    long double ldnum = 1.0L;

    cout << "sizeof(float):       " << sizeof(fnum) << endl; 
    cout << "sizeof(double):      " << sizeof(dnum) << endl;
    cout << "sizeof(long double): " << sizeof(ldnum) << endl; 


    cout << "=======================" << endl;


    /**
     * https://en.cppreference.com/w/cpp/header/iostream <ios> class ios_base
     */
    cout.precision(64);

    /** 
     * float : sign 1bit, exponent 8bits, mantissa 23bits
     * double : sign 1bit, exponent 11bits, mantissa 52bits
     * long double : sign 1bit, exponent 15bits, mantissa 112bits
     */
    unsigned int uint_num;
    float float_num = -118.625f;
    memcpy(&uint_num, &float_num, sizeof(float_num));

    cout << "1100 0010 1110 1101 0100 0000 0000 0000:" << endl;
    cout << "-----------------------" << endl;
    cout << "unsinged int: " << uint_num << endl;
    cout << "float:        " << float_num << endl;


    cout << "=======================" << endl;


    cout << "num0(0.1f), num1(0.02f * 5.0f)" << endl;
    cout << "-----------------------" << endl;
    num0 = 0.1f;
    num1 = 0.02f * 5.0f;

    cout << "num0: " << num0 << endl; 
    cout << "num1: " << num1 << endl; 
    cout << "0.1f: " << 0.1f << endl;
    cout << "0.1:  " << 0.1 << endl;
    cout << "0.1L: " << 0.1L << endl;


    cout << "=======================" << endl;


    num0 = 1.0f;
    num1 = 0.0f;
    cout << "num0(1.0f), num1(0.0f):" << endl;
    cout << "   for (i = 0; i < 1000; i++) num1 += 0.001f; -> 1.0 + err" << endl;
    cout << "-----------------------" << endl;
    for (int i = 0; i < 1000; i++)
        num1 = num1 + 0.001f;
    cout << "num0: " << num0 << endl;
    cout << "num1: " << num1 << endl;
    cout << "-----------------------" << endl;
    
    cout << "num0 == num1: ";
    if (num0 == num1)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    cout << "fabsf(num0-num1) <= FLT_EPSILON: ";   
    if (fabsf(num0 - num1) <= FLT_EPSILON)
        cout << "true" << endl;
    else
        cout << "false" << endl;


    cout << "=======================" << endl;

    /**
     * Derivation FLT_EPSILON
     */
    cout << "Derivation FLT_EPSILON" << endl;
    cout << "-----------------------" << endl;
    /**
     * 0 01111111 00000000000000000000000
     * sign 1bits : 0
     * exponent 8bits : 01111111 (2^0) - 127
     * mantissa 23bits : 00000000000000000000000
     * Value actually stored in float : 1
     */
    unsigned int int_num0 = 0b00111111100000000000000000000000;
    float float_num0;
    memcpy(&float_num0, &int_num0, sizeof(int_num0));
    cout << "float_num0[0b00111111100000000000000000000000]: " << float_num0 << endl;

    /**
     * ADD mantissa 1bit
     * 0 01111111 00000000000000000000000
     * sign 1bits : 0
     * exponent 8bits : 01111111 (2^0) - 127
     * mantissa 23bits : 00000000000000000000001
     * Decimal representation : 1.00000011920928955078125
     */
    unsigned int int_num1 = 0b00111111100000000000000000000001;
    float float_num1;
    memcpy(&float_num1, &int_num1, sizeof(int_num1));
    cout << "float_num1[0b00111111100000000000000000000001]: " << float_num1 << endl;
    cout << "abs(sub)  [0b00000000000000000000000000000001]: 0.00000011920928955078125" << endl;
    cout << "-----------------------" << endl;

    float epsilon = float_num1 - float_num0;
    cout << "epsilon = float_num1 - float_num0: " << epsilon << endl;
    cout << "FLT_EPSILON:                       " << FLT_EPSILON << endl;

    cout << "epsilon == FLT_EPSILON:            ";
    if (epsilon == FLT_EPSILON)
        cout << "true" << endl;
    else
        cout << "false" << endl;


    cout << "=======================" << endl;


    float_num0 = 1.0f;
    int_num1 = 0b00110100000000000000000000000000;
    memcpy(&float_num1, &int_num1, sizeof(int_num1));

    cout << "memory of mantissa is 23bits, float can detect to 2^-23." << endl;
    cout << "127 - 23 = 104: 0110 1000" << endl;
    cout << "-----------------------" << endl;
    cout << "Epsilon: 1.0 * 10^-23 [0b0 0110 1000 00000000000000000000000]" << endl;
    cout << "1.0f:                        " << float_num0 << endl;
    cout << "1.0 * 2^-23:                 " << float_num1 << endl;
    cout << "1.0f + 1.0 * 2^-23:          " << float_num0 + float_num1 << endl;
    cout << "1.0 * 10^-23 == FLT_EPSILON: ";
    if (float_num1 == FLT_EPSILON)
        cout << "true" << endl;
    else
        cout << "false" << endl;


    cout << "=======================" << endl;


    float_num0 = 1.0f;
    int_num1 = 0b00110011100000000000000000000000;
    memcpy(&float_num1, &int_num1, sizeof(int_num1));

    cout << "CASE 2^-24:" << endl;
    cout << "127 - 24 = 103: 0110 0111" << endl;
    cout << "1.0 * 2^-24 [0b0 0110 0111 00000000000000000000000]" << endl;
    cout << "-----------------------" << endl;
    cout << "1.0f:               " << float_num0 << endl;
    cout << "1.0 * 2^-24:        " << float_num1 << endl;
    cout << "1.0f + 1.0 * 2^-24: " << float_num0 + float_num1 << endl;
    cout << "Result:             out of range" << endl;


    cout << "=======================" << endl;


    float_num0 = 1.0f;
    int_num1 = 0b01001011000000000000000000000000;
    memcpy(&float_num1, &int_num1, sizeof(int_num1));

    cout << "CASE 2^23:" << endl;
    cout << "127 + 23 = 150: 1001 0110" << endl;
    cout << "1.0 * 2^23  [0b0 1001 0110 00000000000000000000000]" << endl;
    cout << "-----------------------" << endl;
    cout << "1.0f:              " << float_num0 << endl;
    cout << "1.0 * 2^23:        " << float_num1 << endl;
    cout << "1.0f + 1.0 * 2^23: " << float_num0 + float_num1 << endl;


    cout << "=======================" << endl;


    float_num0 = 1.0f;
    int_num1 = 0b01001011100000000000000000000000;
    memcpy(&float_num1, &int_num1, sizeof(int_num1));

    cout << "CASE 2^24:" << endl;
    cout << "127 + 25 = 104: 1001 0111" << endl;
    cout << "1.0 * 2^24  [0b0 1001 0111 00000000000000000000000]" << endl;
    cout << "-----------------------" << endl;
    cout << "1.0f:              " << float_num0 << endl;
    cout << "1.0 * 2^24:        " << float_num1 << endl;
    cout << "1.0f + 1.0 * 2^24: " << float_num0 + float_num1 << endl;
    cout << "Result:            out of range" << endl;


    cout << "=======================" << endl;


    /**
     * https://en.wikipedia.org/wiki/Exponent_bias
     * 1(127-126) ~ 254(127+127) (0 and 255 have special meanings)
     * 2^-126 ~ 2^127
     * decimal 127 is binary 1111 1110
     */
    cout << "SPECIAL BITS CHECK" << endl;
    cout << "-----------------------" << endl;
    float float_sbits0, float_sbits1, float_sbits2, float_sbits3, float_sbits4, float_sbits5, float_sbits6, float_sbits7;
    unsigned int uint_sbits0 = 0b01111111111111111111111111111111;
    unsigned int uint_sbits1 = 0b00000000011111111111111111111111;
    unsigned int uint_sbits2 = 0b00000000000000000000000000000000;
    unsigned int uint_sbits3 = 0b01111111100000000000000000000000;
    unsigned int uint_sbits4 = 0b11111111111111111111111111111111;
    unsigned int uint_sbits5 = 0b10000000011111111111111111111111;
    unsigned int uint_sbits6 = 0b10000000000000000000000000000000;
    unsigned int uint_sbits7 = 0b11111111100000000000000000000000;
    memcpy(&float_sbits0, &uint_sbits0, sizeof(uint_sbits0));
    memcpy(&float_sbits1, &uint_sbits1, sizeof(uint_sbits1));
    memcpy(&float_sbits2, &uint_sbits2, sizeof(uint_sbits2));
    memcpy(&float_sbits3, &uint_sbits3, sizeof(uint_sbits3));
    memcpy(&float_sbits4, &uint_sbits4, sizeof(uint_sbits4));
    memcpy(&float_sbits5, &uint_sbits5, sizeof(uint_sbits5));
    memcpy(&float_sbits6, &uint_sbits6, sizeof(uint_sbits6));
    memcpy(&float_sbits7, &uint_sbits7, sizeof(uint_sbits7));

    cout << "[0b0 1111 1111 11111111111111111111111]: " << float_sbits0 << endl;
    cout << "[0b0 0000 0000 11111111111111111111111]: " << float_sbits1 << "(subnormal number)" << endl;
    cout << "[0b0 0000 0000 00000000000000000000000]: " << float_sbits2 << endl;
    cout << "[0b0 1111 1111 00000000000000000000000]: " << float_sbits3 << endl;
    cout << "[0b1 1111 1111 11111111111111111111111]: " << float_sbits4 << endl;
    cout << "[0b1 0000 0000 11111111111111111111111]: " << float_sbits5 << "(subnormal number)" << endl;
    cout << "[0b1 0000 0000 00000000000000000000000]: " << float_sbits6 << endl;
    cout << "[0b1 1111 1111 00000000000000000000000]: " << float_sbits7 << endl;


    cout << "-----------------------" << endl;


    uint_num = 0b01111111011111111111111111111111;
    memcpy(&float_num, &uint_num, sizeof(uint_num));

    cout << "[0b0 1111 1110 1111 1111 1111 1111 1111 111]:            " << float_num << endl;
    cout << "FLT_MAX:                                                 " << FLT_MAX << endl;
    
    cout << "FLT_MAX == [0b0 1111 1110 1111 1111 1111 1111 1111 111]: ";
    if (FLT_MAX == float_num)
        cout << "true" << endl;
    else
        cout << "false" << endl;


    cout << "-----------------------" << endl;
    

    uint_num = 0b11111111011111111111111111111111;
    memcpy(&float_num, &uint_num, sizeof(uint_num));

    cout << "[0b1 1111 1110 1111 1111 1111 1111 1111 111]:             " << float_num << endl;
    cout << "-FLT_MAX:                                                 " << -FLT_MAX << endl;

    cout << "-----------------------" << endl;


    uint_num = 0b00000000000000000000000000000001;
    memcpy(&float_num, &uint_num, sizeof(uint_num));

    cout << "[0b0 0000 0000 00000000000000000000001]: " << float_num << endl;
    cout << "FLT_TRUE_MIN(min positive value):        " << FLT_TRUE_MIN << endl;
    cout << "0.00000000000000000000001 * 2^-126 (subnormal number)" << endl;


    cout << "-----------------------" << endl;


    uint_num = 0b00000000100000000000000000000000;
    memcpy(&float_num, &uint_num, sizeof(uint_num));

    cout << "[0b0 0000 0001 00000000000000000000000]: " << float_num << endl;
    cout << "FLT_MIN(min normalized positive value) : " << FLT_MIN << endl;
    cout << "1.0 * 2^-126" << endl;


    cout << "=======================" << endl;

    return 0;
}