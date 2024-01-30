#include <iostream>

using namespace std;

int main(void)
{
    cout << "=======================" << endl;


    cout << "What's your favorite food?" << endl;
    cout << "1) Kimch" << endl;
    cout << "2) Korean BBQ" << endl;
    cout << "3) Chicken" << endl;

    int num;
    cin >> num;

    switch (num) {
    case 1:
        cout << "You selected Kimch" << endl;
        break;
    case 2:
        cout << "You selected Korean BBQ" << endl;
        break;
    case 3:
        cout << "You selected Chicken" << endl;
        break;
    default:
        cout << "Invalid Input" << endl;
    }

    cout << "-----------------------" << endl;

    cout << "What's your favorite food?" << endl;
    cout << "a) Kimch" << endl;
    cout << "b) Korean BBQ" << endl;
    cout << "c) Chicken" << endl;

    char ch;
    cin >> ch;

    switch (ch) {
    case 'a':
    case 'A':
        cout << "You selected Kimch" << endl;
        break;
    case 'b':
    case 'B':
        cout << "You selected Korean BBQ" << endl;
        break;
    case 'c':
    case 'C':
        cout << "You selected Chicken" << endl;
        break;
    default:
        cout << "Invalid Input" << endl;
    }

    cout << "-----------------------" << endl;

    cout << "What's your favorite food?(input upper)" << endl;
    cout << "a) Kimch" << endl;
    cout << "b) Korean BBQ" << endl;
    cout << "c) Chicken" << endl;

    cin >> ch;

    switch (ch) {
    case 'A':
        cout << "Converted to a" << endl;
        [[fallthrough]];
    case 'a':
        cout << "You selected Kimch" << endl;
        break;
    case 'B':
        cout << "Converted to b" << endl;
        [[fallthrough]];
    case 'b':
        cout << "You selected Korean BBQ" << endl;
        break;
    case 'C':
        cout << "Converted to c" << endl;
        [[fallthrough]];
    case 'c':
        cout << "You selected Chicken" << endl;
        break;
    default:
        cout << "Invalid Input" << endl;
    }

    cout << "-----------------------" << endl;

    bool b = true;
    switch (b) {
    case true:
        cout << "true" << endl;
        break;
    default:
        cout << "false" << endl;
    }

    cout << "-----------------------" << endl;

    int selection = 0;

    if (selection == 0)
        cout << 0 << endl;
    else if (selection == 1)
        cout << 1 << endl;
    else if (selection == 2)
        cout << 2 << endl;
    else if (selection == 3)
        cout << 3 << endl;

    cout << "-----------------------" << endl;

    switch (selection) {
    case 0:
        cout << 0 << endl;
        break;
    case 1:
        cout << 1 << endl;
        break;
    case 2:
        cout << 2 << endl;
        break;
    case 3:
        cout << 3 << endl;
        break;
    }

    cout << "-----------------------" << endl;

    cout << "num0 num1: ";
    int num0, num1;
    switch (int count = scanf("%d %d", &num0, &num1)) {
    case 1:
        cout << num0 << endl;
        break;
    case 2:
        cout << num0 << endl;
        cout << num1 << endl;
        break;
    }

    cout << "-----------------------" << endl;

    cout << "num0 num1: ";
    switch (int num0, num1; int count = scanf("%d %d", &num0, &num1)) {
    case 1:
        cout << num0 << endl;
        break;
    case 2:
        cout << num0 << endl;
        cout << num1 << endl;
        break;
    }

    cout << "-----------------------" << endl;

    cout << "after block: (" << num0 << " " << num1 << ")" << endl;


    cout << "=======================" << endl;

    return 0;
}