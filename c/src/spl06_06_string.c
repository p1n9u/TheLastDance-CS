#include <stdio.h>
#include <memory.h>

int main(void)
{
    /**
     * @NULL: ((void*)0), 
     * @NUL: 0, 0x00, '\0'
     */
    // char null1 = NULL;
    char *null1 = NULL;
    char null2 = 0;
    char null3 = '\0';
    char zero = '0';
    printf("%s %d %d %d\n\n", null1, null2, null3, zero);

    /**
     * usage of string, replacement of string
     * ../note/SP06_Arrays_Pointers_and_Strings.md#strings
     */

    return 0;
}