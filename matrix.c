#include <stdio.h>
#include <math.h>
#include <stdbool.h>


typedef struct matrix
{
        int     rows;
        int     cols;
        double  **array;
}       Matrix;


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

    // Allocate memory for each row
        for (int i = 0; i < rows; i++)
        {
                m->array[i] = malloc(cols * sizeof(double));
                if (!m->array[i]) 
                {
                        // Free previous rows
                        for (int j = 0; j < i; j++) free(m->array[j]);
                        free(m->array);
                        free(m);
                        return NULL;
                }
                // Optional: initialize row to 0
                for (int j = 0; j < cols; j++) m->array[i][j] = 0.0;
        }

        return m;
}

void    free_matrix(Matrix *m)
{
        for (int i = 0; i < m->rows; i++)
                free(m->array[i]);
        free(m->array);
        free(m);
}
