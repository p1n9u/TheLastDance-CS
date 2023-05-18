#include <stdio.h>

#define SQ(x)                   ((x) * (x))
#define ADD(x, y, z)            ((x) + (y) + (z))
#define MUL(x, y, z)            ((x) * (y) * (z))
#define MIN(x, y)               (((x) < (y)) ? (x) : (y))
#define MIN4(x, y, z, w)        MIN(MIN(x, y), MIN(z, w))

#define WRONG_SQ(x)             x * x

#define PI                      3.141592
#define AREA_CIRCLE(x)          ((PI) * (x) * (x))

int main(void)
{
    int a = 3, b = 4, c = 5, d = 6;
    printf("SQ(a)               : %d\n", SQ(a));
    printf("ADD(a, b, c)        : %d\n", ADD(a, b, c));
    printf("MUL(a, b, c)        : %d\n", MUL(a, b, c));
    printf("MIN(a, b)           : %d\n", MIN(a, b));
    printf("MIN4(a, b, c, d)    : %d\n", MIN4(a, b, c, d));

    printf("SQ(a + b)           : %d\n", SQ(a + b));
    printf("WRONG_SQ(a + b)     : %d\n", WRONG_SQ(a + b));

    printf("AREA_CIRCLE(1)      : %lf\n", AREA_CIRCLE(1));
    printf("AREA_CIRCLE(5)      : %lf\n", AREA_CIRCLE(5));

    return 0;
}