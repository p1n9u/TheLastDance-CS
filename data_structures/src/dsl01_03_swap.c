#include <stdio.h>

void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(void)
{
    int i = 8, j = 5;
    swap(&i, &j);
    printf("%d %d\n", i, j);

    return 0;
}