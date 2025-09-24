#include "../../inc/cub3d.h"

int	mouse_move(int x, int y, t_data *d)
{
	double	d_x;
	double	a;
	double	old_dx;
	double	old_px;

	(void)y;
	d_x = x - d->prev_mouse_x;
	if (d_x == 0)
		return (0);
	a = d_x * d->mouse_sensitivity;
	old_dx = d->player.dir_x;
	d->player.dir_x = d->player.dir_x * cos(a) - d->player.dir_y * sin(a);
	d->player.dir_y = old_dx * sin(a) + d->player.dir_y * cos(a);
	old_px = d->player.plane_x;
	d->player.plane_x = d->player.plane_x * cos(a) - d->player.plane_y * sin(a);
	d->player.plane_y = old_px * sin(a) + d->player.plane_y * cos(a);
	mlx_mouse_move(d->mlx.mlx_ptr, d->mlx.win_ptr, d->screen.width / 2,
		d->screen.height / 2);
	d->prev_mouse_x = d->screen.width / 2;
	return (0);
}
