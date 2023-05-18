#include <stdio.h>

#define GREETINGS(a, b, c)                          \
do {                                                \
    printf(#a ", " #b ", and " #c " : Hello!\n");   \
} while (0)

#define WRONG_GREETINGS(a, b, c)                    \
do {                                                \
    printf("a, b, c : Hello!\n");                   \
} while (0)

#define EXEC(x) func_##x()

void func_A()
{
    printf("Call A\n");
}

void func_B()
{
    printf("Call B\n");
}

int main(void)
{
    GREETINGS(Alice, Bob, Carole);
    WRONG_GREETINGS(Alice, Bob, Carole);

    EXEC(A);
    EXEC(B);

    return 0;
}
