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

//the determinat of submatrix
double  minor(Matrix a, int row, int column)
{
        Matrix  *s;
        double  m;

        s = submatrix(a, row, column);
        if(s->rows != 2)
                m = determinat(*s);
        else
                m = determinant_2x2(*s);
        free_matrix(s);
        return (m);
}


double  cofactor(Matrix a, int row, int column)
{
        double  m;
        double  c;

        m = minor(a, row, column);
        if((row + column) % 2 == 0)
                c = m;
        else
                c = -m;
        return (c);
}


double  determinat(Matrix a)
{
        int     i;
        double  det;

        if(a.rows == 2 && a.cols == 2)
                return (determinant_2x2(a));
        i = 0;
        det = 0;
        while(i < a.cols)
        {
                det += (a.array[0][i] * cofactor(a, 0, i));
                i++;
        }
        return (det);
}

Matrix  *inverse(Matrix a)
{
        Matrix  *b;
        int     i;
        int     j;
        double  c;
        double  det;

        det = determinat(a);
        if(det == 0)
                return (NULL);
        b = create_matrix(a.rows, a.cols);
        if(!b)
                return (NULL);
        i = 0;
        while(i < a.rows)
        {
                j = 0;
                while(j < a.cols)
                {
                        c = cofactor(a, i, j);
                        b->array[j][i] = (c / det);
                        j++;
                }
                i++;
        }
        return (b);
}


Matrix   *translation(double x, double y, double z)
{
        Matrix  *m;

        m = create_matrix(4, 4);
        if(!m)
                return (NULL);
        m->array[0][0] = 1.0;
        m->array[1][1] = 1.0;
        m->array[2][2] = 1.0;
        m->array[3][3] = 1.0;
        m->array[0][3] = x;
        m->array[1][3] = y;
        m->array[2][3] = z;

        return (m);
}

//moves a point
Tuple   multiply_translation(Tuple p, double x, double y, double z)
{
        Matrix  *m;
        Tuple   t;

        m = translation(x, y, z);
        t = multiply_matrix_tuple(*m, p);
        free_matrix(m);
        return (t);
}

//moves points in reverse
Tuple   multiply_inverse_translation(Tuple p, double x, double y, double z)
{
        Matrix  *m;
        Matrix  *inev;
        Tuple   t;

        m = translation(x, y, z);
        inev = inverse(*m);
        t = multiply_matrix_tuple(*inev, p);
        free_matrix(m);
        free_matrix(inev);
        return (t);
}

//make the image larger or smaller in size
Matrix  *scaling(double x,double y,double z)
{
        Matrix  *m;

        m = create_matrix(4, 4);
                if(!m)
                return (NULL);
        m->array[0][0] = x;
        m->array[1][1] = y;
        m->array[2][2] = z;
        m->array[3][3] = 1.0;

        return (m);
}

Tuple   multiply_scaling(Tuple p, double x, double y, double z)
{
        Matrix  *m;
        Tuple   t;

        m = scaling(x, y, z);
        t = multiply_matrix_tuple(*m, p);
        free_matrix(m);
        return (t);
}


Tuple   multiply_inverse_scaling(Tuple p, double x, double y, double z)
{
        Matrix  *m;
        Tuple   t;
        Matrix  *inev;

        m = scaling(x, y, z);
        inev = inverse(*m);
        t = multiply_matrix_tuple(*inev, p);
        free_matrix(m);
        free_matrix(inev);
        return (t);
}

Tuple   reflection(Tuple p)
{
        Tuple   r;

        r = multiply_scaling(p, -1, 1, 1);
        return (r);
}


//radian pass as (M_PI / 4 = (degrees))
Tuple   rotation_x(Tuple p, double radians)
{
        Tuple   r;
        double  y;
        double  z;

        y = p.y * cos(radians) - p.z * sin(radians);
        z = p.y * sin(radians) + p.z * cos(radians);
        r = point(p.x, y, z);
        return (r);
}