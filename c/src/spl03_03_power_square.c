#include <stdio.h>

/**
 * The Math library is a type of standard library,
 * but the compiler should be informed that it includes the library as follows.
 * 
 * gcc -o spl03_03_power_square spl03_03_power_square -lm
 * lm : library math
 */
#include <math.h>

int main(void)
{
    double x;
    while(1) {
        printf("Input x: ");
        if (scanf("%lf", &x) != 1)
            break;
        if (x >= 0.0) {
            printf("\n%15s %22.15e\n", "sqrt(x)=", sqrt(x));
            printf("\n%15s %22.15e\n", "pow(x, x)=", pow(x, x));
        } else {
            printf("\nNumber must be nonnegative.\n");
            break;
        }
    }
    
    return 0;
}