#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i, n;
    printf("\n%s\n%s",
           "Some randomly distrubuted integers will be printed.",
           "How many do you want to See? ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        if (i % 10 == 0)
            putchar('\n');
        printf("%12d", rand());
    }
    printf("\n\n");

    return 0;
}