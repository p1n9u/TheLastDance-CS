#include <stdio.h>

#define LIMIT 46

int main(void)
{
    long f0 = 0, f1 = 1, n, tmp;
    printf("%7s%19s%29s\n%7s%19s%29s\n\n%7s%19s%29s\n",
           "  ", "Fibonacci", "Fibonacci",
           " n", "  numbers", " quotient",
           "--", "---------", "---------");
    printf("%7d%19d\n%7d%19d\n", 0, 0, 1, 1); /* 1st 2 cases */
    for (n = 0; n <= LIMIT; n++) {
        tmp = f1;
        f1 += f0;
        f0 = tmp;
        printf("%7ld%19ld%29.16f\n", n, f1, (double) f1 / f0);
    }

    return 0;
}
    