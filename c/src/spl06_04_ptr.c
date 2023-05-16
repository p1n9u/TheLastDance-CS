#include <stdio.h>
#include <stdlib.h>

void print_triple_array(const char *title, double (*p)[4][3])
{
    int i, j, k;
    printf("\nPrinting '%s' array\n", title);
    for (i = 0; i < 3; i++) {
        printf("[ ");
        for (j = 0; j < 4; j++) {
            printf("{");
            for (k = 0; k < 3; k++)
                printf("%3.0lf", p[i][j][k]);
            printf("}");
            if (j != 3)
                printf(", ");
        }
        printf(" ]\n");
    }
    printf("\n");
}

int main(void)
{
    int i, j, k;
    double a[3][4][3] = {
        { 
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 },
            { 10, 11, 12 }
        },
        {
            { 13, 14, 15 },
            { 16, 17, 18 },
            { 19, 20, 21 },
            { 22, 23, 24 }
        },
        {
            { 25, 26, 27 },
            { 28, 29, 30 },
            { 31, 32, 33 },
            { 34, 35, 36 }
        }
    };

    print_triple_array("a", a);

    double (*b)[4][3];
    b = (double (*)[4][3])malloc(sizeof(double [4][3]) * 3);
    b = a;
    print_triple_array("b", b);

    double *(*c)[4];
    c = (double *(*)[4])malloc(sizeof(double (*)[4]) * 3);
    /**
     * Do not assignment c[i][j] with malloc()
     */
    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            c[i][j] = (double *)malloc(sizeof(double) * 3);
    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            c[i][j] = b[i][j];
    print_triple_array("c", c);
    
    double ***d;
    d = (double ***)malloc(sizeof(double **) * 3);
    for (i = 0; i < 3; i++)
        d[i] = (double **)malloc(sizeof(double *) * 4);
    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            d[i][j] = (double *)malloc(sizeof(double) * 3);
    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            d[i][j] = c[i][j];

    printf("a[2][3] =  %p\n", a[2][3]);
    printf("b[2][3] =  %p\n", b[2][3]);
    printf("c[2][3] =  %p\n", c[2][3]);
    printf("d[2][3] =  %p\n", d[2][3]);

    printf("a[2][3][0] = %2.0lf\n", a[2][3][0]);
    printf("b[2][3][0] = %2.0lf\n", b[2][3][0]);
    printf("c[2][3][0] = %2.0lf\n", c[2][3][0]);
    printf("d[2][3][0] = %2.0lf\n", d[2][3][0]);

    return 0;
}