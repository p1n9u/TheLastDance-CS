#include <stdio.h>
#include <stdlib.h>

void print_array(int arr[][5])
{
    int i, j;
    for (i = 0; i < 5 ; i++) {
        for (j = 0; j < 5; j++)
            printf("%2d ", arr[i][j]);
        printf("\n");
    }
}

void transpose(int arr[][5], int t_arr[][5])
{
    int i, j;
    for (i = 0; i < 5 ; i++)
        for (j = 0; j < 5; j++)
            t_arr[i][j] = arr[j][i];
}

int main(void)
{
    int arr[5][5] = {
        {1,  2,  3,  4,  5},
        {6,  7,  8,  9,  10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };
    int t_arr[5][5] = {0, };
    printf("===============\n");
    print_array(arr);
    printf("===============\n");
    transpose(arr, t_arr);
    print_array(t_arr);

    return 0;
}