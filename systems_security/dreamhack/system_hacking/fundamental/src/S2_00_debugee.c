/*
 * Name: debugee.c
 * $ gcc -o S2_00_debugee S2_00_debugee.c -no-pie
 */

#include <stdio.h>

int main(void)
{
    int sum = 0;
    int val1 = 1;
    int val2 = 2;
    sum = val1 + val2;
    printf("1 + 2 = %d\n", sum);
    return 0;
}