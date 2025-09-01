#include "../../inc/cub3d.h"

double	calc_move_speed(t_data *data)
{
	return (BASE_MOVE_SPEED * (data->screen.width / REFERENCE_WIDTH));
}

double	calc_rot_speed(t_data *data)
{
	return (BASE_ROT_SPEED * (data->screen.width / REFERENCE_WIDTH));
}

int	pixel_skip(t_data *data)
{
	if (data->screen.width > 1600)
		return (2);
	return (1);
}

t_vec	rotate_vec(double x, double y, double angle)
{
	t_vec	res;

	res.x = x * cos(angle) - y * sin(angle);
	res.y = x * sin(angle) + y * cos(angle);
	return (res);
}