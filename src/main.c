#include "cub3d.h"

int main(int ac, char **av)
{
	t_data	*game;

	if (ac != 2)
		return (mess_error(1, "usage ./cub3D <map>"));
	game = malloc(sizeof(t_data));
	if (!game)
		return (mess_error(1, "Échec malloc"));
	ft_bzero(game, sizeof(t_data));
	game->map = ft_get_map(av[1], game);
	if (ft_check_map(game, av[1]) == 0)
	{
		cleanup(game);
		return (mess_error(1, "invalid map"));
	}
	init_mlx(game);
	init_camera(game);
	mlx_hook(game->mlx.win_ptr, 2, 1L<<0, key_press, game);
	mlx_hook(game->mlx.win_ptr, 3, 1L<<1, key_release, game);
	mlx_hook(game->mlx.win_ptr, 17, 0, close_window, game);
	mlx_loop(game->mlx.mlx_ptr);
	return (0);
}
