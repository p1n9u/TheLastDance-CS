#include <stdio.h>

#define ITER_ERR 100

double my_sqrt(double num)
{
    double sqrt;
    sqrt = 1.0;

    int i;
    for (i = 0; i < ITER_ERR; i++)
        sqrt = (sqrt + num / sqrt) / 2;
    
    return sqrt;
}

int main(void)
{
    double x;
    printf("Insert non-negative number x : ");
    scanf("%lf", &x);
    printf("\nsqrt(x) = %10lf, sqrt(x)^2 = %.30e\n",
           my_sqrt(x),
           my_sqrt(x) * my_sqrt(x));

    return 0;
}