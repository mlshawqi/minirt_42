#ifndef HEADER_H
#define HEADR_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define EPSILON 0.00001




typedef struct {
    double x;
    double y;
    double z;
    double w; //if w=1 -> point if w=0 -> vector
} Tuple;

typedef struct matrix
{
        int     rows;
        int     cols;
        double  **array;
}       Matrix;

typedef struct {
        double red;
        double green;
        double blue;
} Color;


typedef struct
{
        int width;
        int height;
        Color *pixels;  // 1D array to store pixels (row-major order)
} Canvas;


Tuple   point(double x, double y, double z);
Tuple   vector(double x, double y, double z);
bool    scalars_equal(double a, double b);
Tuple   subtract_tuples(Tuple p2, Tuple p1);
Tuple   adding_tuples(Tuple p2, Tuple p1);
Tuple   negate(Tuple t) ;
Tuple   multiply_scalar(Tuple t, double scalar);
Tuple   divide_scalar(Tuple t, double scalar);
double  magnitude(Tuple v);
Tuple   normalize(Tuple v);
double  dot_product(Tuple a, Tuple b);
Tuple   cross(Tuple a, Tuple b);



Color   color(double r, double g, double b);
Color   add_color(Color c1, Color c2);
Color   subtract_color(Color c1, Color c2);
Color   multiply_color(Color c, double scalar);
Color   hadamard_product(Color c1, Color c2);
Canvas canvas(int width, int height);
void    write_pixel(Canvas *c, int x, int y, Color col);
Color   pixel_at(Canvas *c, int x, int y);
void free_canvas(Canvas *c);



Matrix  *create_matrix(int rows, int cols);
void    free_matrix(Matrix *m);








#endif