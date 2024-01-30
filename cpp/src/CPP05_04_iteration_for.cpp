#include <iostream>
#include <limits>

using namespace std;

void clear_input_buffer();

int main(void)
{
    cout << "=======================" << endl;


    int i;

    for (i = 0; i < 10; ++i)
        cout << i << " ";
    cout << endl;

    cout << "-----------------------" << endl;

    for (i = 0; i; ++i)
        cout << i << " ";
    cout << endl;

    cout << "-----------------------" << endl;

    for (i = 10; i; --i)
        cout << i << " ";
    cout << endl;

    cout << "-----------------------" << endl;

    for (int i = 0; i < 10; i += 2)
        cout << i << " ";
    cout << endl;

    cout << "-----------------------" << endl;

    for (int i = 0, j = 0; i < 10 && j < 10; i += 1, j += 2) {
        cout << i << endl;
        cout << j << endl;
    }

    cout << "-----------------------" << endl;

    for (int i = 0; i < 10; ++i) {
        if (i % 3 == 0)
            break;
        if (i % 5 == 0)
            break;

        cout << i << endl;
    }

    cout << "-----------------------" << endl;

    for (int i = 0; i < 10; ++i) {
        if (i % 3 == 0)
            continue;

        cout << i << " ";
    }
    cout << endl;

    cout << "-----------------------" << endl;

    for (i = 0; i < 10; ++i) {
        cout << i << " ";
        if (i == 9)
            break;
    }
    cout << endl;
    cout << i << endl;

    cout << "-----------------------" << endl;

    for (i = 0; i < 10; ++i)
        cout << i << " ";
    cout << endl;
    cout << i << endl;

    cout << "-----------------------" << endl;

    for (;;) {
        cout << "Food" << endl;
        cout << "1) Kimch" << endl;
        cout << "2) BBQ" << endl;
        cout << "3) Chicken" << endl;

        int num;
        cin >> num;

        bool needToBreak = false;

        switch (num) {
        case 1:
            cout << "Kimch" << endl;
            needToBreak = true;
            break;
        case 2:
            cout << "BBQ" << endl;
            needToBreak = true;
            break;
        case 3:
            cout << "Chicken" << endl;
            needToBreak = true;
            break;
        }

        if (needToBreak)
            break;

        clear_input_buffer();
    }

    cout << "-----------------------" << endl;

    for (;;) {
        cout << "Food" << endl;
        cout << "1) Kimch" << endl;
        cout << "2) BBQ" << endl;
        cout << "3) Chicken" << endl;

        int num;
        cin >> num;

        switch (num) {
        case 1:
            cout << "Kimch" << endl;
            break;
        case 2:
            cout << "BBQ" << endl;
            break;
        case 3:
            cout << "Chicken" << endl;
            break;
        default:
            clear_input_buffer();
            continue;
        }

        break;
    }

    cout << "-----------------------" << endl;

    int num;
    cout << "fac: ";
    cin >> num;

    clear_input_buffer();

    int total = 1;
    for (; num; num--)
        total *= num;
    cout << total << endl;

    cout << "-----------------------" << endl;

    for (char ch = 'a'; ch <= 'z'; ++ch)
        cout << ch << " ";
    cout << endl;

    cout << "-----------------------" << endl;

    cout << "fib: ";
    cin >> num;

    clear_input_buffer();

    if (num < 2) {
        cout << num << endl;
    } else {
        int pre_value = 0;
        int cur_value = 1;
        for (int i = 0; i < num - 1; ++i) {
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