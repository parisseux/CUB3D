#include "../../inc/cub3d.h"

int key_hook(int keycode, t_data *game)
{
    if (keycode == 53) // ESC macOS | check pour Linux
    {
        cleanup(game);
        exit(0);
    }
    return (0);
}

int close_window(t_data *game)
{
    cleanup(game);
    exit(0);
    return (0);
}

void cleanup(t_data *game)
{
    if (game->map)
    {
        for (int i = 0; game->map[i]; i++)
            free(game->map[i]);
        free(game->map);
    }
    if (game->mlx.img_ptr)
        mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
    if (game->mlx.win_ptr)
        mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
    if (game->mlx.mlx_ptr)
    {
		#ifdef __APPLE__
				free(game->mlx.mlx_ptr);
		#else
				mlx_destroy_display(game->mlx.mlx_ptr);
				free(game->mlx.mlx_ptr);
		#endif
    }
    free(game);
}
