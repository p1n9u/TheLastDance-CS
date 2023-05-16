#include <stdio.h>

#define N 10

int main(void)
{
    int i, *p, sum = 0;
    int a[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    /*
     * p = a;
     * is equivalent to 
     * p = &a[0];
     */
    p = a;

    /*
     * p = a + 1;
     * is equivalent to 
     * p = &a[1];
     */
    p = a + 1;

    for (p = a; p < &a[N]; p++)
        sum += *p;
    printf("%d\n", sum);

    sum = 0;
    for (i = 0; i < N; i++)
        sum += *(a + i);
    printf("%d\n", sum);

    p = a;
    sum = 0;
    for (i = 0; i < N; i++)
        sum += p[i];
    printf("%d\n", sum);

    printf("%p\n", &a);
    // a++;
    // a += 2;
    // a = p;

    return 0;
}