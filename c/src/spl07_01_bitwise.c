#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void bit_print(int a)
{
    int i;
    /*
     * bytes to bits
     * 4 * 8
     */
    int n = sizeof(int) * CHAR_BIT;
    /*
     * 10000000 00000000 00000000 00000000
     */
    int mask = 1 << (n - 1);

    /*
     * compare a's msb with mask n times.
     */
    for (i = 1; i <= n; i++) {
        putchar(((a & mask) == 0) ? '0' : '1');
        a <<= 1;
        if (i % CHAR_BIT == 0 && i < n)
            putchar(' ');
    }
    putchar('\n');
}

int pack(char a, char b, char c, char d)
{
    int p;

    p = a;
    p = (p << CHAR_BIT) | b;
    p = (p << CHAR_BIT) | c;
    p = (p << CHAR_BIT) | d;

    return p;
}

char unpack(int p, int k)
{
    int n = k * CHAR_BIT;
    /**
     * @mask: 00000000 00000000 00000000 11111111
     */
    unsigned mask = 255;

    mask <<= n;
    return ((p & mask) >> n);
}


int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("usage:      bitwise num1 num2\n");
        printf("recomand:   bitwise 150  255\n");
        printf("recomand:   bitwise 150  -16777216\n");
        exit(1);
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    printf("%d\t%d\t:\n", num1, num2);
    bit_print(num1);
    bit_print(num2);

    printf("~%d\t~%d\t:\n", num1, num2);
    bit_print(~num1);
    bit_print(~num2);

    printf("%d & %d\t:\n", num1, num2);
    bit_print(num1 & num2);

    printf("%d | %d\t:\n", num1, num2);
    bit_print(num1 | num2);

    printf("%d ^ %d\t:\n", num1, num2);
    bit_print(num1 ^ num2);

    printf("%d << 2\t%d >> 5\t:\n", num1, num2);
    bit_print(num1 << 2);
    bit_print(num2 >> 5);

    char c1 = 'H';
    char c2 = 'Y';
    char c3 = 'U';
    char c4 = 'E';

    printf("%c %c %c %c:\n", c1, c2, c3, c4);
    bit_print(c1);
    bit_print(c2);
    bit_print(c3);
    bit_print(c4);

    int p_data = pack(c1, c2, c3, c4);
    printf("packed data:\n");
    bit_print(p_data);

    int i;
    printf("unpacked data:\n");
    for (i = 0; i < sizeof(int); i++) {
        putchar(unpack(p_data, i));
    }
    printf("\n\n");

    return 0;
}
