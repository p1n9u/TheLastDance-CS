/*
 * gcc
 * -D[MACRO]
 * 
 * gcc -o spl08_02_condition spl08_02_condition.c
 * Debug: May 18 2023 10:33:08 spl08_02_condition.c 14
 * Debug
 * 
 * gcc -o spl08_02_condition spl08_02_condition.c -DVERSION=123
 * Debug: May 18 2023 10:32:44 spl08_02_condition.c 14
 * Version: 1.2.3
 * 
 * gcc -o spl08_02_condition spl08_02_condition.c -DVERSION=12
 * Debug: May 18 2023 10:34:10 spl08_02_condition.c 22
 * Version: 1.2.7
 */
#include <stdio.h>

#define DEBUG

int main(void)
{
#ifdef DEBUG
    printf("Debug: %s %s %s %d\n",
           __DATE__, __TIME__, __FILE__, __LINE__);
#endif

#if (defined DEBUG || defined TEST) && !defined (VERSION)
    printf("Debug\n");
#endif

#if (VERSION == 123)
    printf("Version: 1.2.3\n");
#elif (VERSION == 127)
    printf("Version: 1.2.7\n");
#endif

    return 0;
}