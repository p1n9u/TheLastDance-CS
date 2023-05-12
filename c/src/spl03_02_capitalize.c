#include <stdio.h>

int main(void)
{
    int c;
    /**
     * To input EOF
     * Linux : Ctrl + D
     * Windows : Ctrl + Z 
     */
    while ((c = getchar()) != EOF) {
        if (c >= 'a' && c <= 'z')
            putchar(c + 'A' - 'a');
        else
            putchar(c);
    }
    
    return 0;
}