#include "../../inc/cub3d.h"

void get_screen_size(t_data *data)
{
    typedef struct {
        char *name;
        int width;
        int height;
        char *description;
    } t_resolution_profile;
    
    t_resolution_profile profiles[] = {
        {"tryhard", 800, 600, "Performance max"},
        {"balanced", 1280, 720, "Équilibrée"},
        {"quality", 1440, 900, "Deustsche qualität"},
        {"mid-screen-linux", 1920, 1080, "Moitie taille pc linux"},
        {"full-screen-linux", 3840, 2160, "Taille pc école, lag de fou"}
    };
    
    int choisis_la_resolution_chacal = 3;
    
    data->screen.width = profiles[choisis_la_resolution_chacal].width;
    data->screen.height = profiles[choisis_la_resolution_chacal].height;
    
    printf("Resolution profile: %s (%s)\n", 
           profiles[choisis_la_resolution_chacal].name, 
           profiles[choisis_la_resolution_chacal].description);
    printf("Window size: %dx%d\n", data->screen.width, data->screen.height);
}

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
    
    // Configurer la résolution
    get_screen_size(data);
    data->sky_scale = 4.0;
    data->sky_offset = 0.0;
    
    load_texture(data, &data->tex_north, data->no_texture);
    load_texture(data, &data->tex_south, data->so_texture);
    load_texture(data, &data->tex_west, data->we_texture);
    load_texture(data, &data->tex_east, data->ea_texture);
    load_texture(data, &data->tex_floor, data->floor_texture);
    load_texture(data, &data->tex_sky, data->sky_texture);
    
    data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, data->screen.width, data->screen.height, "cub3D");
    if (!data->mlx.win_ptr)
    {
        cleanup(data);
        mess_error(1, "Window creation failed");
    }
    data->mlx.img_ptr = mlx_new_image(data->mlx.mlx_ptr, data->screen.width, data->screen.height);
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
