#include <stdio.h>
#include <string.h>

int main(void)
{
    char str1[10];
    strcpy(str1, "STAR");
    const char *str2 = "BUCKS";
    printf("str1: %s\t\tstr2: %s\n", str1, str2);
    printf("strlen(str1): %lu\t\tstrlen(str2): %lu\n",
           strlen(str1), strlen(str2));

    strcat(str1, str2);
    printf("str1: %s\t\tstr2: %s\n", str1, str2);
    printf("strlen(str1): %lu\t\tstrlen(str2): %lu\n",
           strlen(str1), strlen(str2));

    if (strcmp(str1, str2) == 0)
        printf("str1 is equal to str2!\n");
    else
        printf("str1 is not equal to str2...\n");

    return 0;
}