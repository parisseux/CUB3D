#include "cub3d.h"

int main(int ac, char **av)
{
    t_data	*game;

    if (ac != 2)
        return (mess_error(1, "usage ./cub3D <map>"));
    game = malloc(sizeof(t_data));
    if (!game)
		return (1);
    ft_bzero(game, sizeof(t_data));
    game->map = ft_get_map(av[1], game);
    if (ft_check_map(game, av[1]) == 0)
		  return (mess_error(1, "invalid map"));
    int i = 0;
    while (game->map[i])
    {
        printf("%s\n", game->map[i]);
        i++;
    }
    free(game);
    return (0);
}
