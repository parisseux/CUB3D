#include "minilibx_linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    void *mlx_ptr;
    void *img_ptr;
    int width, height;

    mlx_ptr = mlx_init();
    if (!mlx_ptr)
    {
        fprintf(stderr, "Error: MLX init failed\n");
        return (1);
    }
    img_ptr = mlx_xpm_file_to_image(mlx_ptr, "./textures/north.xpm", &width, &height);
    if (!img_ptr)
    {
        fprintf(stderr, "Error: Failed to load texture ./textures/north.xpm\n");
        return (1);
    }
    printf("Texture loaded successfully: width=%d, height=%d\n", width, height);
    mlx_destroy_image(mlx_ptr, img_ptr);
    mlx_destroy_display(mlx_ptr);
    free(mlx_ptr);
    return (0);
}