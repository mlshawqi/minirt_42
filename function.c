#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define EPSILON 0.00001

typedef struct {
    double x;
    double y;
    double z;
    double w; //if w=1 -> point if w=0 -> vector
} Tuple;


Tuple   point(double x, double y, double z)
{
        Tuple   t;

        t.x = x;
        t.y = y;
        t.z = z;
        t.w = 1.0;
        return (t);
}

Tuple   vector(double x, double y, double z)
{
        Tuple   t;

        t.x = x;
        t.y = y;
        t.z = z;
        t.w = 0.0;
        return (t);
}


bool    float_equal(double a, double b)
{
        if (fabs(a - b) < EPSILON)
                return (true);
        else
                return (false);
}

//to find direction between p1 and p2
Tuple   subtract_tuples(Tuple p2, Tuple p1)
{
        Tuple   v;

        v.x = p2.x - p1.x;
        v.y = p2.y - p1.y;
        v.z = p2.z - p1.z;
        v.w = p2.w - p1.w;
        return v;
}

//p1 is point and p2 is a vector 
Tuple   adding_tuples(Tuple p2, Tuple p1)
{
        Tuple   v;

        v.x = p1.x + p2.x;
        v.y = p1.y + p2.y;
        v.z = p1.z + p2.z;
        v.w = p1.w + p2.w;
        return v;
}

//Negating a tuple flips its direction
Tuple   negate(Tuple t) {
        Tuple       result;
        result.x = -t.x;
        result.y = -t.y;
        result.z = -t.z;
        result.w = t.w;

        return (result);
}

Tuple   multiply_scalar(Tuple t, double scalar)
{
        Tuple   result;

        result.x = t.x * scalar;
        result.y = t.y * scalar;
        result.z = t.z * scalar;
        result.w = t.w;
        return (result);
}

Tuple   divide_scalar(Tuple t, double scalar)
{
        Tuple   result;

        result.x = t.x / scalar;
        result.y = t.y / scalar;
        result.z = t.z / scalar;
        result.w = t.w;
        return (result);
}



double  magnitude(Tuple v)
{
        double  sum_of_squares;

        sum_of_squares = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
        return sqrt(sum_of_squares);
}

Tuple   normalize(Tuple v)
{
        double  mag;
        Tuple  result;

        mag = magnitude(v);   // find the length first
        result.x = v.x / mag; // divide each component by the length
        result.y = v.y / mag;
        result.z = v.z / mag;

        return result;
}

double  dot_product(Tuple a, Tuple b)
{
        double  dot;

        dot = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
        return (dot);
}

Tuple   cross(Tuple a, Tuple b)
{
        Tuple   result;

        result.x = a.y * b.z - a.z * b.y;
        result.y = a.z * b.x - a.x * b.z;
        result.z = a.x * b.y - a.y * b.x;
        result.w = 0.0; // always a vector
        return result;
}