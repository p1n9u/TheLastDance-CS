#include <stdio.h>

int gcd(int a, int b)
{
    int tmp;

    /*
     * Works without this part.
     */
    // if (b > a) {    
    //     tmp = a;
    //     a = b;
    //     b = tmp;
    // }
    
    /*
     * If b > a, variables are automatically exchanged in the first step.
     */
    while (b) {
        tmp = a % b;
        a = b;
        b = tmp;
    }

    return a;
}

int main(void)
{
    printf("gcd(10, 15) = %d\n",    gcd(10, 15));       /* 5 */
    printf("gcd(125, 13) = %d\n",   gcd(125, 13));      /* 1 */
    printf("gcd(625, 225) = %d\n",  gcd(625, 225));     /* 25 */
    printf("gcd(6840, 324) = %d\n", gcd(6840, 324));    /* 36 */

    return 0;
}