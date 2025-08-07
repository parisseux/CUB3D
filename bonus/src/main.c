#include "../inc/cub3d.h"

t_data *init_data()
{
	t_data *game;

	game = malloc(sizeof(t_data));
	if (!game)
		return (NULL);
	ft_bzero(game, sizeof(t_data));
	game->screen.width = 1280;
	game->screen.height = 720;
	game->sky_scale = 4.0;
    game->sky_offset = 0.0;
	return (game);
}

int main(int ac, char **av)
{
	t_data	*game;

	if (ac != 2)
		return (mess_error(1, "usage ./cub3D <map>"));
	game =  init_data();
	if (!game)
		return (mess_error(1, "Échec initialisation structure data"));
	game->map = ft_get_map(av[1], game);
	if (!game->map)
	{
		cleanup(game);
		return (mess_error(1, "loading map"));
	}
	int i = 0;
	while(game->map[i])
	{
		printf("%s\n", game->map[i]);
		i++;
	}
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
