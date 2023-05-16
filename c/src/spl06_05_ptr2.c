#include <stdio.h>

int main(void)
{
    char a[4][10] = {"HaHa",
                     "han yang ",
                     "cheese",
                     " Iphone"};
    char *pc[4] = { a[0], a[1], a[2], a[4] };
    char **ppc = pc;

    printf("%s", *ppc +2);
    printf("%c", *(*(ppc + 1) + 2));
    printf("%s", *(ppc + 1) + 4);
    printf("%c", *(*(ppc + 2)));
    printf("%s\n", *(ppc + 2) + 4);

    return 0;
}