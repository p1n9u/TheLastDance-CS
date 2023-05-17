#include <stdio.h>
#include <string.h>

char *my_strcat(char *s1, const char *s2)
{
    char *cur1 = s1;
    while (*cur1 != '\0') {
        cur1++;
    }

    const char *cur2 = s2;
    do {
        *cur1 = *cur2;
        cur1++;
        cur2++;
    } while (*cur2 != '\0');

    return s1;
}

int my_strcmp(const char *s1, const char *s2)
{
    int c;
    const char *cur1 = s1, *cur2 = s2;

    c = 0;
    do {
        if (*cur1 != *cur2) {
            c = *cur1 - *cur2;
            break;
        }
        cur1++;
        cur2++;
    } while ((*cur1 != '\0') ||
             (*cur2 != '\0'));

    return c;
}

int main(void)
{
    char *str1 = "STARBUCKS";
    char str2[10] = "STAR";
    char *str3 = "BUCKS";

    printf("strcmp():\t %d\n", strcmp(str1, str2));
    printf("my_strcmp():\t %d\n", my_strcmp(str1, str2));
    printf("strcmp():\t %d\n", strcmp(str2, str1));
    printf("my_strcmp():\t %d\n", my_strcmp(str2, str1));
    printf("%s\n", my_strcat(str2, str3));
    printf("%d\n", my_strcmp(str1, str2));

    return 0;
}