#include "header.h"


// void print_matrix(Matrix *m)
// {
//     for (int i = 0; i < m->rows; i++)
//     {
//         for (int j = 0; j < m->cols; j++)
//             printf("%.5f ", m->array[i][j]);
//         printf("\n");
//     }
// }

// int main() {
//     // Tuple p = point(2, 3, 4);
//     // Tuple transform = shearing(p, 0, 0, 0, 0, 0, 1);

//     // printf("Result: point(%.0f, %.0f, %.0f)\n", transform.x, transform.y, transform.z);

//     // Expected output: point(5, 3, 4)
//     return 0;
// }

typedef struct s_point3d
{
    double x;
    double y;
    double z;
} t_point3d;


int main(void)
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 400, 300, "Clock Example");

    int canvas_w = 400;
    int canvas_h = 300;
    double scale = 100.0; // scale factor for visibility

    // 12 o'clock in 3D (x,z plane)
    Tuple p = {0, 0, 1, 1};

    // Draw all 4 main hours: 12, 3, 6, 9
    for (int i = 0; i < 12; i++)
    {
        Tuple temp = p; // copy point
        Matrix *r = rotation_y(i * M_PI / 6);

        // Multiply point by rotation matrix
        temp = multiply_matrix_tuple(*r, temp);

        // Map 3D point to 2D screen (x-z plane)
        int screen_x = (int)(temp.x * scale + canvas_w / 2);
        int screen_y = (int)(temp.z * scale + canvas_h / 2);

        mlx_pixel_put(mlx, win, screen_x, screen_y, 0x00FF00);

        free_matrix(r); 
    }

    mlx_loop(mlx);

    mlx_destroy_window(mlx, win);
    mlx_destroy_display(mlx);
    free(mlx);
    return 0;
}
