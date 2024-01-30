#include <iostream>

using namespace std;

void clear_input_buffer();

int main(void)
{
    cout << "=======================" << endl;


    int i = 0;
    while (i < 10) {
        cout << i << " ";
        i++;
    }
    cout << endl;

    i = 0;
    do {
        cout << i << " ";
        i++;
    } while (i < 10);
    cout << endl;

    cout << "-----------------------" << endl;

    i = 0;
    while (i < 0) {
        cout << i << " ";
        i++;
    }
    cout << endl;

    i = 0;
    do {
        cout << i << " ";
        i++;
    } while (i < 0);
    cout << endl;

    cout << "-----------------------" << endl;

    int num;

    cout << "num: ";
    cin >> num;

    clear_input_buffer();

    do {
        if (num % 3 == 0)
            break;
        if (num % 5 == 0)
            break;

        cout << "wow" << endl;
    } while (false);

    cout << "abcd" << endl;

    cout << "-----------------------" << endl;

    cout << "fac: ";
    cin >> num;
    clear_input_buffer();

    int total = 1;
    do {
        total *= num;
    } while (--num);
    cout << total << endl;

    cout << "-----------------------" << endl;

    char ch = 'a';
    do {
        cout << ch << " ";
    } while (++ch <= 'z');
    cout << endl;

    cout << "-----------------------" << endl;

    cout << "fib: ";
    cin >> num;
    clear_input_buffer();

    if (num <= 1) {
        cout << num << endl;
    } else {
        int pre_value = 0;
        int cur_value = 1;
        do {
            int next_value = pre_value + cur_value;
            pre_value = cur_value;
            cur_value = next_value;
        } while (--num - 1);

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