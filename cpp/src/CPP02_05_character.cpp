#include <iostream>

using namespace std;

int main(void)
{
    cout << "=======================" << endl;


    /**
     * string
     */
    cout << "h" << " is string" << endl;

    /**
     * char
     */
    cout << 'h' << " is char" << endl;


    cout << "=======================" << endl;


    /**
     * relation with integer
     */
    char ch0 = 'a';
    char ch1 = 97;

    cout << "ch0 : " << ch0 << endl;
    cout << "ch1 : " << ch1 << endl;
    cout << "-----------------------" << endl;
    /**
     * C Style
     */
    cout << "ch0 : " << (int)ch0 << endl;
    /**
     * C++ Style
     */
    cout << "ch1 : " << int(ch1) << endl;

    cout << (char)97 << endl;
    cout << 97 << endl;


    cout << "=======================" << endl;


    /**
     * sizeof operator
     */
    cout << "sizeof(char): " << sizeof(char) << endl;
    cout << "sizeof(char *): " << sizeof(char *) << endl;
    cout << "sizeof(string): " << sizeof(string) << endl;


    cout << "=======================" << endl;


    /**
     * https://en.wikipedia.org/wiki/ASCII
     */
    cout << "New Line" << endl;
    cout << "Hello World";
    cout << '\n';
    cout << "Hello World";
    cout << endl;
    cout << "-----------------------" << endl;
    cout << "Tab" << endl;
    cout << "Hello World";
    cout << '\t';
    cout << "Hello World";
    cout << endl;
    cout << "-----------------------" << endl;
    cout << "Backspace" << endl;
    cout << "Hello World";
    cout << '\b';
    cout << "Hello World";
    cout << endl;
    cout << "-----------------------" << endl;
    cout << "Audio" << endl;
    cout << "Hello World";
    cout << '\a';
    cout << "Hello World";
    cout << endl;
    cout << "-----------------------" << endl;
    cout << "Single Quotation Mark" << endl;
    cout << "Hello World";
    cout << '\'';
    cout << "Hello World";
    cout << endl;
    cout << "-----------------------" << endl;
    cout << "Double Quotation Mark" << endl;
    cout << "\"Hello World\"";
    cout << "Hello World";
    cout << endl;
    cout << "-----------------------" << endl;
    cout << "Hex" << endl;
    cout << '\x61';
    cout << endl;
    cout << "-----------------------" << endl;
    cout << "Oct" << endl;
    cout << '\141';
    cout << endl;


    cout << "=======================" << endl;


    /**
     * MultiCharacter Literal - not standard
     *
     * {
     *     char ch = 'ab';
     *     int num = 'ab';
     *     cout << ch << endl;
     *     cout << num << endl;
     * }
     */

     return 0;
}