#include "../../inc/cub3d.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

static void load_texture(t_data *data, t_texture *tex, char *path)
{
    int width;
    int height;

    printf("Loading texture: %s\n", path);
    tex->img_ptr = mlx_xpm_file_to_image(data->mlx.mlx_ptr, path, &width, &height);
    if (!tex->img_ptr)
    {
        printf("Error: Failed to load image %s\n", path);
        cleanup(data);
        mess_error(1, "Invalid texture file");
    }
    tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->size_line, &tex->endian);
    if (!tex->data)
    {
        printf("Error: Failed to get texture data for %s\n", path);
        cleanup(data);
        mess_error(1, "Failed to get texture data");
    }
    printf("Texture loaded: %s, width=%d, height=%d, bpp=%d, size_line=%d, endian=%d\n", 
           path, width, height, tex->bpp, tex->size_line, tex->endian);
    tex->width = width;
    tex->height = height;
}

void init_mlx(t_data *data)
{
    data->mlx.mlx_ptr = mlx_init();
    if (!data->mlx.mlx_ptr)
        mess_error(1, "MLX init failed");
    load_texture(data, &data->tex_north, data->no_texture);
    load_texture(data, &data->tex_south, data->so_texture);
    load_texture(data, &data->tex_west, data->we_texture);
    load_texture(data, &data->tex_east, data->ea_texture);
    data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
    if (!data->mlx.win_ptr)
    {
        cleanup(data);
        mess_error(1, "Window creation failed");
    }
    data->mlx.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!data->mlx.img_ptr)
    {
        cleanup(data);
        mess_error(1, "Image creation failed");
    }
    data->mlx.img_data = mlx_get_data_addr(data->mlx.img_ptr, &data->mlx.bpp, &data->mlx.size_line, &data->mlx.endian);
    if (!data->mlx.img_data)
    {
        cleanup(data);
        mess_error(1, "Image data retrieval failed");
    }
    mlx_loop_hook(data->mlx.mlx_ptr, update, data);
}
