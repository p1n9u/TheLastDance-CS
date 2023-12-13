#include <cstdio>
#include <iostream>

using namespace std;

void clear_input_buffer();

int main(void)
{ 
    cout << "=======================" << endl;


    int num, x;
    printf("num: ");
    scanf("%d", &num);
    while (getchar() != '\n');
    printf("%d\n", num);
    

    cout << "-----------------------" << endl;

    /**
     * scanf()
     *
     * Return: count of input value from first to last success continuosly.
     */
    char ch;
    printf("num ch num: ");
    int n = scanf("%d %c %d", &num, &ch, &x);
    while (getchar() != '\n');
    printf("%d\n", n);

    cout << "-----------------------" << endl;

    printf("num: ");
    if (scanf("%d", &num)) {
        while (getchar() != '\n');
        printf("%d\n", num);
    }

    cout << "-----------------------" << endl;

    printf("num0 + num1 = num2: ");
    int num0, num1, num2;
    /**
     * input: 10 + 20 = 40
     */
    scanf("%d + %d = %d", &num0, &num1, &num2);
    while (getchar() != '\n');
    printf("%d + %d = %d\n", num0, num1, num2);

    cout << "-----------------------" << endl;

    /**
     * 10 -> 10
     * 0x10 -> 16
     * 010 -> 8
     */
    printf("num(prefix): ");
    scanf("%i", &num);
    while (getchar() != '\n');
    printf("%i\n", num);

    cout << "-----------------------" << endl;

    printf("ch: ");
    scanf("%c", &ch);
    while (getchar() != '\n');
    printf("%c\n", ch);
    printf("%d\n", ch);

    cout << "-----------------------" << endl;
    
    printf("float double double: ");
    float f0;
    double d0, d1;
    scanf("%lf %lf %f", &d0, &d1, &f0);
    printf("%lf %lf %f\n", d0, d1, f0);

    cout << "-----------------------" << endl;
    
    printf("octal: ");
    scanf("%o", &num);
    printf("%d\n", num);

    cout << "-----------------------" << endl;
    
    clear_input_buffer();

    printf("ch: ");
    scanf("%c", &ch);
    printf("1, %c\n", ch);

    clear_input_buffer();

    printf("ch: ");
    scanf("%c", &ch);
    printf("2, %c\n", ch);

    cout << "-----------------------" << endl;

    freopen("ch03_02_input.txt", "r", stdin);
    scanf("%d", &num);
    printf("%d\n", num);


    cout << "=======================" << endl;

    return 0;
}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}