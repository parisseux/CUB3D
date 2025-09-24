#include "../inc/cub3d.h"

static t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_bzero(data, sizeof(t_data));
	data->screen.width = 1280;
	data->screen.height = 720;
	data->sky_scale = 4.0;
	data->move_speed = calc_move_speed(data);
	data->rot_speed = calc_rot_speed(data);
	data->mouse_sensitivity = 0.0001;
	data->prev_mouse_x = data->screen.width / 2;
	return (data);
}

static void	init_mlx_hook(t_data *data)
{
	mlx_hook(data->mlx.win_ptr, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win_ptr, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx.win_ptr, 6, 1L << 6, mouse_move, data);
	mlx_mouse_hide(data->mlx.mlx_ptr, data->mlx.win_ptr);
	mlx_hook(data->mlx.win_ptr, 17, 0, close_window, data);
	mlx_loop(data->mlx.mlx_ptr);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (mess_error(1, "usage ./cub3D_bonus <map>"));
	data = init_data();
	if (!data)
		return (mess_error(1, "Échec initialisation structure data"));
	data->map = ft_get_map(av[1], data);
	if (!data->map)
	{
		cleanup(data);
		return (mess_error(1, "loading map"));
	}
	if (ft_check_map(data, av[1]) == 0)
	{
		cleanup(data);
		return (mess_error(1, "invalid map"));
	}
	init_mlx(data);
	init_camera(data);
	init_mlx_hook(data);
	return (0);
}
