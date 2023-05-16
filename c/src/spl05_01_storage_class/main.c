/*
 * gcc -o storage main.c extern.c static.c
 */
#include <stdio.h>

int a = 1, b = 2, c = 3;

int extern_function(void);
int static_function(void);

int main(void)
{
    printf("%3d\n", extern_function());     /* 12    : 4 + 4 + 4 */
    printf("%3d %3d %3d\n", a, b, c);       /* 4 2 3 : b, c is blocked */
    static_function();
    static_function();

    return 0;
}