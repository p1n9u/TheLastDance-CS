#include <cstdio>

int main(void)
{
    printf("%d + %d = %i\n", 2, 3, 2 + 3);
    printf("%u + %u = %u\n", 3, 2, 3 + 2);
    printf("%u\n", -1);
    printf("%hhu\n", -1);
    char ch = 'b';
    printf("%c%c\n", 'a', ch);
    printf("%f - %f = %lf\n", 2.0, 3.0f, -1.0f);
    printf("%o, %x, %X\n", 10, 10, 10);
    printf("%hhx\n", 255);
    printf("%hhx\n", 256);
    printf("%010d\n", 1);
    printf("%010d\n", -1);
    printf("%010f\n", 1.1);
    printf("%010f\n", -1.1);
    printf("%010.1f\n", 1.1);
    printf("%010.1f\n", -1.1);
    printf("%10d\n", 1);
    printf("%10d\n", -1);
    printf("%10f\n", 1.1);
    printf("%10f\n", -1.1);
    printf("%-10d\n", 1);
    printf("%-10d\n", -1);
    printf("%-10f\n", 1.1);
    printf("%-10f\n", -1.1);
    printf("%%\n");
    freopen("CPP03_01_output.txt", "w", stdout);
    printf("Hello World!");

    return 0;
}