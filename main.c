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
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1}
    };
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            A->array[i][j] = a_vals[i][j];

    printf("Original Matrix A:\n");
    print_matrix(A);

    // Get submatrix by removing row 2 and column 1
    Matrix *S = submatrix(*A, 2, 1);

    printf("\nSubmatrix(A, 2, 1):\n");
    if (S)
        print_matrix(S);
    else
        printf("Submatrix is NULL\n");

    free_matrix(A);
    if (S)
        free_matrix(S);

    return 0;
}