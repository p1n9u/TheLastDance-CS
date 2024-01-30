#include <iostream>

using namespace std;

int main(void)
{
    cout << "=======================" << endl;


    int num = 0;
    
    if (num == 0)
        cout << "Executed true" << endl;

    if (num != 0)
        cout << "Executed false" << endl;

    if (num = 1)
        cout << "assignment" << endl;

    if (0 == num)
        cout << "equalt to" << endl;

    cout << "-----------------------" << endl;

    num = 0;

    if (num != 0) {
        cout << "wow" << endl;
        cout << "wow1" << endl;
    }

    cout << "-----------------------" << endl;

    int num0 = 0;
    int num1 = 1;

    if (num0 == 0)
        if (num1 == 1)
            cout << "wow" << endl;

    if (num0 == 0) {
        if (num1 == 1) {
            cout << "wow" << endl;
        }
    }

    if (num0 == 0 && num1 == 1)
        cout << "and wow" << endl;

    cout << "-----------------------" << endl;

    num0 = 0;

    if (num0++ == 0 && num0++ == 1)
        cout << num0 << endl;

    num0 = 0;

    if (num0++ + num0++ == 1)
        cout << num0 << endl;

    cout << "-----------------------" << endl;

    num0 = 0;
    
    if (num0 == 0)
        cout << "num0 == 0" << endl;
    else
        cout << "!(num0 == 0)" << endl;

    cout << (num0 == 0 ? "num0 == 0" : "!(num0 == 0)") << endl;

    cout << "-----------------------" << endl;

    num0 = 1;
    if (num0 == 0)
        cout << "num0 == 0" << endl;
    else if (num0 == 1)
        cout << "num0 == 1" << endl;

    cout << "-----------------------" << endl;

    int score;
    cout << "score: ";
    cin >> score;
    
    char grade;
    
    if (score == 100)
        grade = 'A';
    else if (90 <= score && score < 100)
        grade = 'B';
    else if (80 <= score && score < 90)
        grade = 'C';
    else
        grade = 'D';
    
    cout << grade << endl;

    cout << "-----------------------" << endl;

    int score0 = 90;
    int score1 = 80;

    if (score0 >= 90 && score1 >= 90)
        ;
    else
        cout << "fail0" << endl;

    if (!(score0 >= 90 && score1 >= 90))
        cout << "fail1" << endl;
    if (!(score0 >= 90) || !(score1 >= 90))
        cout << "fail2" << endl;
    if (score0 < 90 || score1 < 90)
        cout << "fail3" << endl;

    cout << "-----------------------" << endl;

    cout << "num0 num1: ";
    if (int count = scanf("%d %d", &num0, &num1))
        printf("count : %d (%d %d)\n", count, num0, num1);
    else
        printf("fail count : %d\n", count);

    cout << "-----------------------" << endl;

    cout << "num0 num1: ";
    if (int num0, num1; int count = scanf("%d %d", &num0, &num1))
        printf("count : %d (%d %d)\n", count, num0, num1);
    else
        printf("fail count : %d\n", count);

    cout << "-----------------------" << endl;

    cout << "after block: (" << num0 << " " << num1 << ")" << endl;


    cout << "=======================" << endl;

    return 0;
}