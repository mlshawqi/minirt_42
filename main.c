#include "header.h"


void print_matrix(Matrix *m)
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
            printf("%.0f ", m->array[i][j]);
        printf("\n");
    }
}


int main(void)
{
    Matrix *A = create_matrix(4, 4);

    // Fill matrix A
    double a_vals[4][4] = {
        {0, 9, 3, 0},
        {9, 8, 0, 8},
        {1, 8, 5, 3},
        {0, 0, 5, 8}
    };
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            A->array[i][j] = a_vals[i][j];

    printf("Original Matrix A:\n");
    print_matrix(A);

    // Transpose matrix A in place
    transposing_matrix(*A);

    printf("\nTransposed Matrix A:\n");
    print_matrix(A);

    free_matrix(A);

    return 0;
}