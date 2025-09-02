#include "header.h"


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

Tuple   rotation_y(Tuple p, double radians)
{
        Tuple   r;
        double  x;
        double  z;

        x = p.x * cos(radians) + p.z * sin(radians);
        z = -(p.x) * sin(radians) + p.z * cos(radians);
        r = point(x, p.y, z);
        return (r);
}

Tuple   rotation_z(Tuple p, double radians)
{
        Tuple   r;
        double  x;
        double  y;

        x = p.x * cos(radians) - p.y * sin(radians);
        y = p.x * sin(radians) + p.y * cos(radians);
        r = point(x, y, p.z);
        return (r);
}

Tuple   shearing(Tuple p, double xy, double xz, double yx, double yz, double zx, double zy)
{
        Tuple   s;
        double  x;
        double  y;
        double  z;

        x = p.x + (xy * p.y) + (xz * p.z);
        y = p.y + (yx * p.x) + (yz * p.z);
        z = p.z + (zx * p.x) + (zy * p.y);

        s = point(x, y, z);
        return (s);
}