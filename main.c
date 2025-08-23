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
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}
    };
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            A->array[i][j] = a_vals[i][j];

    printf("Original Matrix A:\n");
    print_matrix(A);

    // Calculate minor for (row=1, column=0)
    double m = determinat(*A);

    printf("\ndet = %.2f\n", m);

    free_matrix(A);

    return 0;
}


