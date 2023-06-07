#include <stdio.h>

int check_adult(int age);

int main(void)
{
    printf("%d\n", check_adult(20));
    printf("%d\n", check_adult(2));
    printf("%d\n", check_adult(-1));

    return 0;
}

int check_adult(int age)
{
    if (age >= 20)
        return 1;
    else if (age < 20 && age >= 0)
        return 0;
    else
        return 2;
}