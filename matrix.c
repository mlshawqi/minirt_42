#include "header.h"


Matrix    *allocate_mtx(Matrix *m, int rows, int cols)
{
        int     i;
        int     j;

        i = 0;
        while (i < rows)
        {
                j = 0;
                m->array[i] = malloc(cols * sizeof(double));
                if (!m->array[i]) 
                {
                        m->rows = i;
                        free_matrix(m);
                        return NULL;
                }
                while (j < cols)
                {
                        m->array[i][j] = 0.0;
                        j++;
                }
                i++;
        }
        return (m);
}

Matrix  *create_matrix(int rows, int cols)
{
        Matrix *m;

        m = malloc(sizeof(Matrix));
        if (!m)
                return NULL;
        m->rows = rows;
        m->cols = cols;
        // Allocate memory for rows
        m->array = malloc(rows * sizeof(double*));
        if (!m->array)
        {
                free(m);
                return NULL;
        }
        return (allocate_mtx(m, rows, cols));
}

void    free_matrix(Matrix *m)
{
        int     i;

        i = 0;
        while (i < m->rows)
        {
                free(m->array[i]);
                i++;
        }
        free(m->array);
        free(m);
}


bool    comparing_matrix(Matrix a, Matrix b)
{
        int     i;
        int     j;

        if(a.rows != b.rows || a.cols != b.cols)
                return (false);
        i = 0;
        j = 0;
        while(i < a.rows)
        {
                j = 0;
                while(j < a.cols)
                {
                        if(scalars_equal(a.array[i][j], b.array[i][j]))
                                j++;
                        else
                                return (false);
                }
                i++;
        }
        return (true);
}

double  c_scalar(Matrix a, Matrix b, int i, int j)
{
        int     k;
        int     sum;

        sum = 0;
        k = 0;
        while(k < b.cols)
        {
                sum += (a.array[i][k] * b.array[k][j]);
                k++;
        }
        return (sum);
}

Matrix  *multiply_matrix(Matrix a, Matrix b)
{
        Matrix  *c;
        int     i;
        int     j;

        if(a.rows != b.cols || a.cols != b.rows)
                return (NULL);
        c = create_matrix(a.rows, b.cols);
        if(!c)
                return (NULL);
        i = 0;
        j = 0;
        while(i < a.rows)
        {
                j = 0;
                while(j < b.cols)
                {
                       c->array[i][j] = c_scalar(a, b, i, j);
                       j++;
                }
                i++;
        }
        return (c);
}

Tuple  multiply_matrix_tuple(Matrix a, Tuple p)
{
        Tuple   c;
        Tuple   pa;
        int     i;
        double     t[4];

        i = 0;
        while(i < a.rows)
        {
                pa = point(a.array[i][0], a.array[i][1], a.array[i][2]);
                pa.w = a.array[i][3];
                t[i] = dot_product(p, pa);
                i++;
        }
        c.x = t[0];
        c.y = t[1];
        c.z = t[2];
        c.w = t[3];
        return (c);
}


void print_matrix(Matrix *m)
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
            printf("%6.2f ", m->array[i][j]);
        printf("\n");
    }
}

int main(void)
{
    Matrix *A = create_matrix(4, 4);

    // Fill matrix A
    double a_vals[4][4] = {
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1}
    };
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            A->array[i][j] = a_vals[i][j];

    // Create tuple b ← tuple(1, 2, 3, 1)
    Tuple b = point(1, 2, 3);

    // Multiply matrix by tuple
    Tuple result = multiply_matrix_tuple(*A, b);

    printf("Matrix A:\n");
    print_matrix(A);
    printf("\nTuple b: (%.2f, %.2f, %.2f, %.2f)\n", b.x, b.y, b.z, b.w);
    printf("\nResult of A * b: (%.2f, %.2f, %.2f, %.2f)\n", result.x, result.y, result.z, result.w);

    free_matrix(A);

    return 0;
}

