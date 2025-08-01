#include "../../inc/cub3d.h"

// game->player.pos_x = j + 0.5
// game->player.pos_y = i + 0.5
//		-> Centre de la case
// game->map[i][j] = '0'
//		-> Remplacer par 0 le joueur
int	init_player(t_data *game)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
				game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				if (player_count > 0)
					return (mess_error(0, "/!\\ Plusieurs joueurs"));
				player_count++;
				game->player.pos_x = j + 0.5;
				game->player.pos_y = i + 0.5;
				game->player.orientation = game->map[i][j];
				game->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (player_count == 0)
		return (mess_error(0, "/!\\ Aucun joueur"));
	return (1);
}
