#include <stdio.h>

int compute_sum(int n);

int main(void)
{
    int n = 3, sum;
    printf("%d\n", n);
    sum = compute_sum(n);
    printf("%d\n", n);
    printf("%d\n", sum);

    return 0;
}

int compute_sum(int n)
{
    int sum = 0;
    for (; n > 0; n--)
        sum += n;
    return sum;
}