#include "../../inc/cub3d.h"

#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	720
#define MOVE_SPEED	0.07
#define ROT_SPEED	0.025

void	init_camera(t_data *data)
{
	t_player	*p;

	p = &data->player;
	if (p->orientation == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (p->orientation == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	else if (p->orientation == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (p->orientation == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
	data->keys.w = 0;
	data->keys.s = 0;
	data->keys.a = 0;
	data->keys.d = 0;
	data->keys.left = 0;
	data->keys.right = 0;
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 53 || keycode == 65307)
	{
		cleanup(data);
		exit(0);
	}
	if (keycode == 13 || keycode == 119)
		data->keys.w = 1;
	if (keycode == 1 || keycode == 115)
		data->keys.s = 1;
	if (keycode == 0 || keycode == 97)
		data->keys.a = 1;
	if (keycode == 2 || keycode == 100)
		data->keys.d = 1;
	if (keycode == 123 || keycode == 65361)
		data->keys.left = 1;
	if (keycode == 124 || keycode == 65363)
		data->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 13 || keycode == 119)
		data->keys.w = 0;
	if (keycode == 1 || keycode == 115)
		data->keys.s = 0;
	if (keycode == 0 || keycode == 97)
		data->keys.a = 0;
	if (keycode == 2 || keycode == 100)
		data->keys.d = 0;
	if (keycode == 123 || keycode == 65361)
		data->keys.left = 0;
	if (keycode == 124 || keycode == 65363)
		data->keys.right = 0;
	return (0);
}
