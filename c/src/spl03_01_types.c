#include <stdio.h>

int main(void)
{
    printf("The sizeof some fundamental types.\n\n");
    printf("char:               %3lu bytes.\n", sizeof(char));
    printf("short:              %3lu bytes.\n", sizeof(short));
    printf("unsigned short:     %3lu bytes.\n", sizeof(unsigned short));
    printf("int:                %3lu bytes.\n", sizeof(int));
    printf("unsigned:           %3lu bytes.\n", sizeof(unsigned));
    printf("long:               %3lu bytes.\n", sizeof(long));
    printf("unsigned long:      %3lu bytes.\n", sizeof(unsigned long));
    printf("long long:          %3lu bytes.\n", sizeof(long long));
    printf("unsigned long long: %3lu bytes.\n", sizeof(unsigned long long));

    return 0;
}