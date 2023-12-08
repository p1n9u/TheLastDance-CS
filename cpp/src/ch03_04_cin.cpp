#pragma warning(disable: 4996)

#include <iostream>
#include <limits>

using namespace std;

int main(void)
{
    cout << "=======================" << endl;
    

    cout << "num: ";
    int num;

    cin >> num;
    cout << num << endl;

    if (cin.fail())
        cin.clear();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "if num: ";
    if (cin >> num)
        cout << num << endl;
    else
        cout << "NaN" << endl;

    if (cin.fail())
        cin.clear();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "-----------------------" << endl;

    char ch;
    cout << "ch: ";
    cin >> ch;
    cout << ch << endl;

    if (cin.fail())
        cin.clear();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "ch: ";
    cin >> ch;
    cout << ch << endl;

    if (cin.fail())
        cin.clear();
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "-----------------------" << endl;

    cout << "num: ";
    cin >> num;
    cout << num << endl;
    cout << num << endl;

    cout << "-----------------------" << endl;

    bool b;

    cout << "boolean: ";
    cin >> b;
    cout << b << endl;

    if (cin.fail())
        cin.clear();
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cin.setf(ios_base::boolalpha);
    cout << "boolean alpha: ";
    cin >> b;
    cout << b << endl;

    if (cin.fail())
        cin.clear();
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "-----------------------" << endl;
    
    cin.setf(ios_base::hex, ios_base::basefield);
    cout << "hex: ";
    cin >> num;
    cout << num << endl;

    if (cin.fail())
        cin.clear();
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "hex: ";
    cin >> hex >> num;
    cout << num << endl;

    if (cin.fail())
        cin.clear();
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "-----------------------" << endl;

    freopen("input.txt", "r", stdin);

    cin >> num;
    cout << num << endl;


    cout << "=======================" << endl;

    return 0;
}