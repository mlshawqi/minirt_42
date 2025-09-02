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

int main() {
    Tuple p = point(2, 3, 4);
    Tuple transform = shearing(p, 0, 0, 0, 0, 0, 1);

    printf("Result: point(%.0f, %.0f, %.0f)\n", transform.x, transform.y, transform.z);

    // Expected output: point(5, 3, 4)
    return 0;
}



