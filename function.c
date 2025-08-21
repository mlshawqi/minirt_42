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