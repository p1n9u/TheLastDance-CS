#include <stdio.h>

#define N 5

int get_max(int arr[])
{
    int max = arr[0];

    int i;
    for (i = 1; i < N; i++)
        if (arr[i] > max)
            max = arr[i];

    return max;
}

int main(void)
{
    int a[N] = {1, 2, 3, 4, 5};
    printf("max: %d\n", get_max(a));

    return 0;
}