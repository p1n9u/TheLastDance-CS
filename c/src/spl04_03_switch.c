#include <stdio.h>
#include <ctype.h> /* for tolower() */

int main(void)
{
    char ch;
    printf("Type character...\n");
    while(1) {
        ch = tolower(getchar());
        if (ch == 'q')
            break;

        switch (ch) {
        case 'a':
            printf("You typed A.\n");
            break;
        case 'b':
            printf("You typed B.\n");
            break;
        case 0x63:
            printf("You typed C.\n");
            break;
        case 0x1b:
            printf("You typed ESC.\n");
            break;
        }
    }

    return 0;
}
