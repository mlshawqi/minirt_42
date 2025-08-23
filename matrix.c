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


// turn rows into columns and columns rows
void  transposing_matrix(Matrix a)
{
        int     i;
        int     j;
        double  tmp;

        i = 0;
        j = 0;
        while(i < a.rows)
        {
                j = i;
                while(j < a.cols)
                {
                        tmp = a.array[i][j];
                        a.array[i][j] = a.array[j][i];
                        a.array[j][i] = tmp;
                        j++;
                }
                i++;
        }
}


double  determinant_2x2(Matrix a)
{
        double  d;

        d = (a.array[0][0] * a.array[1][1]) - (a.array[0][1] * a.array[1][0]);
        return (d);
}


//delete a row and column from a matrix
Matrix  *submatrix(Matrix a, int row, int cols)
{
        Matrix  *s;
        int     i;
        int     j;
        int     k;
        int     m;

        if(a.rows <= 2 || a.cols <= 2)
                return (NULL);
        s = create_matrix(a.rows - 1, a.cols - 1);
        if(!s)
                return (NULL);
        i = 0;
        k = 0;
        while(i < a.rows)
        {
                j = 0;
                m = 0;
                while(i != row && j < a.cols)
                {
                        if(j != cols)
                        {
                                s->array[k][m] = a.array[i][j];
                                m++;
                        }
                        j++;
                }
                if(i != row)
                        k++;
                i++;
        }
        return (s);
}
