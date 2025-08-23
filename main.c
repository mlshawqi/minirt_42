#include "header.h"


void print_matrix(Matrix *m)
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
            printf("%.5f ", m->array[i][j]);
        printf("\n");
    }
}


int main(void)
{
    Matrix *A = create_matrix(4, 4);
    Matrix  *b;

    // Fill matrix A
    double a_vals[4][4] = {
        {8, -5, 9, 2},
        {7, 5, 6, 1},
        {-6, 0, 9, 6},
        {-3, 0, -9, -4}
    };
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            A->array[i][j] = a_vals[i][j];

    printf("Original Matrix A:\n");
    print_matrix(A);

    // Calculate minor for (row=1, column=0)
    b = inverse(*A);

    printf("\n----------------\n");
    print_matrix(b);

    free_matrix(A);
    free_matrix(b);

    return 0;
}


