#include <iostream>

using namespace std;

int main(void)
{
    cout << "=======================" << endl;

    
    int num = 40 - 32 / 2;
    cout << num << endl;
    
    num = 4 - 6 + 2 + 8 / 2 / 2 * 2;
    cout << num << endl;

    int a, b, c;    
    a = b = c = 10;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;

    
    num = 10;
    cout << -1 << endl;
    cout << +-+-+-1 << endl;

    num = 0;
    cout << ++num << endl;
    cout << --num << endl;
    cout << num++ << endl;
    cout << num-- << endl;

    num = 10;
    num += 5;
    cout << num << endl;

    num -= 5;
    cout << num << endl;

    num *= 5;
    cout << num << endl;

    num /= 5;
    cout << num << endl;

    num %= 5;
    cout << num << endl;

    num = 10;
    cout << ++num + num++ << endl; 
    cout << num << endl;

    printf("%d %d\n", ++num, ++num); 
    printf("%d\n", num);


    cout << "=======================" << endl;
    
    return 0;
}
