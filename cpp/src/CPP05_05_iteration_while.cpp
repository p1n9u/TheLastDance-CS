#include <iostream>

using namespace std;

void clear_input_buffer();

int main(void)
{
    cout << "=======================" << endl;


    int i = 0;

    cout << "while: ";
    while (i < 10) {
        cout << i << " ";
        ++i;
    }
    cout << endl;

    cout << "for:   ";
    for (int i = 0; i < 10; ++i)
        cout << i << " ";
    cout << endl;

    cout << "-----------------------" << endl;

    i = 0;
    while (i < 10) {
        if (i % 3 == 0) {
            ++i;
            continue;
        }
        cout << i << " ";
        ++i;
    }
    cout << endl;

    for (int i = 0; i < 10; ++i) {
        if (i % 3 == 0) {
            continue;
        }
        cout << i << " ";
    }
    cout << endl;

    cout << "-----------------------" << endl;

    int num;
    cout << "fac: ";
    cin >> num;

    clear_input_buffer();

    int total = 1;
    while (num)
        total *= num--;

    cout << total << endl;

    cout << "-----------------------" << endl;

    char ch = 'a';
    while (ch <= 'z')
        cout << ch++ << " ";
    cout << endl;

    cout << "-----------------------" << endl;
    
    cout << "fib: ";
    cin >> num;

    clear_input_buffer();
    
    if (0 == num) {
        cout << 0 << endl;
    } else {
        int pre_value = 0;
        int cur_value = 1;
        while (--num) {
            int next_value = pre_value + cur_value;
            pre_value = cur_value;
            cur_value = next_value;
        }
        cout << cur_value << endl;
    }


    cout << "=======================" << endl;

    return 0;
}

void clear_input_buffer()
{
    int c;
    cin.clear();
    while ((c = getchar()) != '\n' && c != EOF);
}