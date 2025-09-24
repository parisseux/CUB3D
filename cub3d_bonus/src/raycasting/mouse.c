#include "../../inc/cub3d.h"

int mouse_move(int x, int y, t_data *data)
{
	double	delta_x;
	double	angle;
	double	old_dir_x;
	double	old_plane_x;
	(void)y;

    delta_x = x - data->prev_mouse_x;
    if (delta_x == 0)
        return 0;
    angle = delta_x * data->mouse_sensitivity;
    old_dir_x = data->player.dir_x;
    data->player.dir_x = data->player.dir_x * cos(angle) - data->player.dir_y * sin(angle);
    data->player.dir_y = old_dir_x * sin(angle) + data->player.dir_y * cos(angle);
    old_plane_x = data->player.plane_x;
    data->player.plane_x = data->player.plane_x * cos(angle) - data->player.plane_y * sin(angle);
    data->player.plane_y = old_plane_x * sin(angle) + data->player.plane_y * cos(angle);
    mlx_mouse_move(data->mlx.mlx_ptr, data->mlx.win_ptr, data->screen.width / 2, data->screen.height / 2);
    data->prev_mouse_x = data->screen.width / 2;
    return 0;
}