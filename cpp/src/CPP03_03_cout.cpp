#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    cout << "=======================" << endl;


    cout << 1 << endl;
    cout.operator<<(1).operator<<(endl);

    cout << "-----------------------" << endl;

    cout << 'a' << 'b' << endl;
    cout.put('a').put('b').put('\n');
    cout.write("ab\n", 3);

    cout << "-----------------------" << endl;

    cout.width(10);
    cout << 1 << endl;

    cout << "-----------------------" << endl;

    cout.width(10);
    cout.fill('#');
    cout << 1 << endl;
    cout.fill(' ');

    cout << "-----------------------" << endl;

    float num = 0.1234567;
    cout << num << endl;

    cout.precision(2);
    cout << num << endl;

    cout.precision(64);
    cout << num << endl;

    cout << "-----------------------" << endl;

    /**
     * setf() - set floag
     * @arg1: flag
     */
    cout.setf(ios_base::showpos);
    cout << 1 << endl;
    cout << 2 << endl;

    cout.unsetf(ios_base::showpos);
    cout << 1 << endl;
    cout << 2 << endl;

    cout << "-----------------------" << endl;

    cout.setf(ios_base::boolalpha);
    cout << true << endl;
    cout << false << endl;

    cout.unsetf(ios_base::boolalpha);
    cout << true << endl;
    cout << false << endl;

    cout << "-----------------------" << endl;

    /**
     * @arg1: internal, left, right(defualt)
     * @arg2: mask
     */
    cout.setf(ios_base::internal, ios_base::adjustfield);
    cout.width(10);
    cout << -10 << 20 << endl;

    cout.setf(ios_base::left, ios_base::adjustfield);
    cout.width(10);
    cout << -10 << 20 << endl;

    cout.setf(ios_base::right, ios_base::adjustfield);
    cout.width(10);
    cout << -10 << 20 << endl;

    cout << "-----------------------" << endl;

    /**
     * @arg1: oct, hex, dec
     * @arg2: mask
     */
    cout.setf(ios_base::oct, ios_base::basefield);
    cout << 16 << endl;

    cout.setf(ios_base::hex, ios_base::basefield);
    cout << 16 << endl;

    cout.setf(ios_base::dec, ios_base::basefield);
    cout << 16 << endl;

    cout << "-----------------------" << endl;

    cout << hex << 16 << endl;
    cout << oct << 16 << endl;
    cout << dec << 16 << endl;

    cout << "-----------------------" << endl;

    hex(cout);
    cout << 16 << endl;

    oct(cout);
    cout << 16 << endl;

    dec(cout);
    cout << 16 << endl;

    cout << "-----------------------" << endl;

    /**
     * setwidth
     * setfill
     * setprecision
     * showpositive
     */
    cout << setw(10) << setfill('#') << setprecision(2) << showpos << 1.1f << endl;


    freopen("CPP03_03_output.txt", "w", stdout);
    cout << "Hello World" << endl;


    cout << "=======================" << endl;

    return 0;
}
