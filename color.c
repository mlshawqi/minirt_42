#include "header.h"


Color   color(double r, double g, double b)
{
    Color c = {r, g, b};
    return c;
}

Color   add_color(Color c1, Color c2)
{
        Color       result;

        result.red = c1.red + c2.red;
        result.green = c1.green + c2.green;
        result.blue = c1.blue + c2.blue;

        return result;
}

Color   subtract_color(Color c1, Color c2)
{
        Color       result;

        result.red = c1.red - c2.red;
        result.green = c1.green - c2.green;
        result.blue = c1.blue - c2.blue;

        return result;
}

Color   multiply_color(Color c, double scalar)
{
        Color       result;

        result.red = c.red * scalar;
        result.green = c.green * scalar;
        result.blue = c.blue * scalar;

        return result;
}

// Hadamard product multiply two colors component-wise
Color   hadamard_product(Color c1, Color c2)
{
        Color   result;

        result.red = c1.red * c2.red;
        result.green = c1.green * c2.green;
        result.blue = c1.blue * c2.blue;

        return result;
}


Canvas canvas(int width, int height)
{
    Canvas c;
    int total_pixels;
    int i;

    c.width = width;
    c.height = height;

    total_pixels = width * height;

    c.pixels = (Color *)malloc(sizeof(Color) * total_pixels);
    if (!c.pixels)
    {
        fprintf(stderr, "Error: could not allocate memory for canvas\n");
        exit(1);
    }

    // Initialize every pixel to black (0,0,0)
    for (i = 0; i < total_pixels; i++)
    {
        c.pixels[i] = color(0, 0, 0);
    }

    return c;
}

void    write_pixel(Canvas *c, int x, int y, Color col)
{
        int index;

        index = y * c->width + x;
        c->pixels[index] = col;
}

//read the color at a location in the canvas after writing it
Color   pixel_at(Canvas *c, int x, int y)
{
        int     index;

        index = y * c->width + x;
        return c->pixels[index];
}


void free_canvas(Canvas *c)
{
    free(c->pixels);
    c->pixels = NULL;
}