#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
    cout << "=======================" << endl;

    /**
     * NOT: '~'
     * 0 -> 1
     * 1 -> 0
     */
    
    /**
     * 0000,0000,0000,0000,0000,0000,0000,0000 (0)
     * cout << "=======================" << endl;
     */
    int int_num = 0;
    cout << ~int_num << endl;

    cout << "-----------------------" << endl;

    /**
     * 0000,0000,0000,0000,0000,0000,0000,0000 (0)
     * 1111,1111,1111,1111,1111,1111,1111,1111 (2^32 - 1)
     */
    unsigned int uint_num = 0;
    cout << ~uint_num << endl;

    cout << "-----------------------" << endl;

    /**
     * 0000,0000,0000,0000,0000,0000,0000,0001 (1)
     * 1111,1111,1111,1111,1111,1111,1111,1110 (2^32 - 2)
     * 0000,0000,0000,0000,0000,0000,0000,0001 (1)
     */
    uint_num = 1;
    cout << ~uint_num << endl;
    cout << ~~uint_num << endl;

    cout << "-----------------------" << endl;

    /**
     * AND: '&'
     * 1 & 1 == 1
     * 1 & 0 == 0
     * 0 & 1 == 0
     * 0 & 0 == 0
     */

    /**
     * 0000,0101 == 5 == 4 + 1 == 2^2 + 2^0
     * 0000,1010 == 10 == 8 + 2 == 2^3 + 2^1
     * 0000,0000 == 0
     */
    int int_num0 = 5;
    int int_num1 = 10;
    int result = int_num0 & int_num1;
    cout << result << endl;

    cout << "-----------------------" << endl;

    /**
     * 0000,0101 == 5 == 4 + 1 == 2^2 + 2^0
     * 0000,1011 == 10 == 8 + 2 == 2^3 + 2^1 + 2^0
     * 0000,0001 == 1
     */
    int_num0 = 5;
    int_num1 = 11;
    result = int_num0 & int_num1;
    cout << result << endl;

    cout << "-----------------------" << endl;

    uint32_t uint32_num = 5;

    result = uint32_num & (int)pow(2, 0);
    cout << result << endl;

    result = uint32_num & (int)pow(2, 1);
    cout << result << endl;

    result = uint32_num & (int)pow(2, 2);
    cout << result << endl;

    result = uint32_num & ((int)pow(2, 0) + (int)pow(2, 1));
    cout << result << endl;

    int flag = (int)pow(2, 0) + (int)pow(2, 2);
    if ((uint32_num & flag) == flag)
        cout << "flag!" << endl;

    cout << "-----------------------" << endl;
    
    /**
     * OR: '|'
     * 1 | 1 == 1
     * 1 | 0 == 1
     * 0 | 1 == 1
     * 0 | 0 == 0
     */

    uint32_num = 0u;

    uint32_num |= (int)pow(2, 0);
    cout << uint32_num << endl;

    uint32_num |= (int)pow(2, 0);
    cout << uint32_num << endl;

    cout << "-----------------------" << endl;

    /**
     * 0000,0000,0000,0000,0000,0000,0000,0101 = 5
     * 1111,1111,1111,1111,1111,1111,1111,1011 AND
     * 0000,0000,0000,0000,0000,0000,0000,0001 = 1
     */
    uint32_num = 5u;

    uint32_num &= ~((int)pow(2, 2));
    cout << uint32_num << endl;

    cout << "-----------------------" << endl;

    /**
     * XOR: '^'
     * 1 ^ 1 == 0
     * 1 ^ 0 == 1
     * 0 ^ 1 == 1
     * 0 ^ 0 == 0
     */

    /**
     * 0000,0101 = 5
     * 0000,1010 = 10
     * 0000,1111 = 15
     */
    int_num0 = 5;
    int_num1 = 10;

    cout << (int_num0 ^ int_num1) << endl;

    cout << "-----------------------" << endl;

    uint32_num = 0u;

    uint32_num ^= (int)pow(2, 0);
    cout << uint32_num << endl;

    uint32_num ^= (int)pow(2, 0);
    cout << uint32_num << endl;

    uint32_num ^= (int)pow(2, 0);
    cout << uint32_num << endl;

    cout << "-----------------------" << endl;

    int a = 1, b = 3, c = 2, d = 1, e = 2;
    cout << (a ^ b ^ c ^ d ^ e) << endl;
    cout << (a ^ d ^ c ^ e ^ b) << endl; // ��ȯ ��Ģ

    cout << "-----------------------" << endl;

    /**
     * LEFTSHIFT: '<<'
     */

    cout << (1 << 0) << endl;
    cout << (1 << 1) << endl;
    cout << (1 << 2) << endl;
    cout << (1 << 3) << endl;

    /**
     * 10000011001000010101011000000000 (2200000000)
     * 000011001000010101011000000000
     * 00001100100001010101100000000000
     */
    int_num = 2200000000;
    int_num <<= 2;

    cout << int_num << endl;

    int_num = 0u;
    int_num |= (1 << 2);
    cout << int_num << endl;

    cout << "-----------------------" << endl;

    /**
     * RIGHTSHIFT: '>>'
     */

    cout << (16 >> 1) << endl;
    cout << (8 >> 1) << endl;
    cout << (4 >> 1) << endl;
    cout << (2 >> 1) << endl;
    cout << (1 >> 1) << endl;
    cout << (14 >> 1) << endl;
    cout << (15 >> 1) << endl;
    cout << (14 >> 2) << endl;
    cout << (15 >> 2) << endl;


    cout << "=======================" << endl;

    return 0;
}