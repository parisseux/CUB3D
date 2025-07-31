#include "../../inc/cub3d.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

void init_mlx(t_data *game)
{
    game->mlx.mlx_ptr = mlx_init();
    if (!game->mlx.mlx_ptr)
        exit(mess_error(1, "Échec initialisation MiniLibX"));
    game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
    if (!game->mlx.win_ptr)
        exit(mess_error(1, "Échec création fenêtre"));
    game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!game->mlx.img_ptr)
        exit(mess_error(1, "Échec création l'image"));
    game->mlx.img_data = mlx_get_data_addr(game->mlx.img_ptr, &game->mlx.bpp, &game->mlx.size_line, &game->mlx.endian);
    if (!game->mlx.img_data)
        exit(mess_error(1, "Échec obtention données de l'image"));
}
