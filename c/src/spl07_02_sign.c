#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

void print_sign(int a)
{
    printf(" %c %c %c %c \n",
           a/(256 * 256 * 256),
           a/(256 * 256),
           a/(256),
           a);
}

void moving_sign(char _a, char _b, char _c, char _d)
{
    int p;

    p = _a;
    p = (p << CHAR_BIT) | _b;
    p = (p << CHAR_BIT) | _c;
    p = (p << CHAR_BIT) | _d;
    
    unsigned mask = 0b11111111000000000000000000000000;
    unsigned tmp;

    while(1) {
        tmp = 0;
        tmp = (p & mask) >> (3 * CHAR_BIT);
        system("clear");
        print_sign(p);
        p = (p << CHAR_BIT) | tmp;
        sleep(1);
    }
}

int main(void)
{
    moving_sign('H', 'Y', 'U', 'E');
    return 0;
}