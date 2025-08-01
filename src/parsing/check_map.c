#include "../../inc/cub3d.h"

int	ft_check_border_map(char **map, int i, int j)
{
	if (i <= 0 || j <= 0 || !map[i + 1] || !map[i][j + 1])
		return (0);
	if (is_space(map[i - 1][j - 1]) || is_space(map[i - 1][j]) || is_space(map[i - 1][j + 1]))
		return (0);
	if (is_space(map[i][j - 1]) || is_space(map[i][j + 1]))
		return (0);
	if (is_space(map[i + 1][j - 1]) || is_space(map[i + 1][j]) || is_space(map[i + 1][j + 1]))
		return (0);
	return (1);
}

int	ft_check_walls(t_data *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] != '1' && is_space(game->map[i][j]) == 0)
			{
				if (ft_check_border_map(game->map, i, j) == 0)
				{
					printf("DEBUG\nChar \"%c\" found at pos : %d|%d (abs|ord)\n", game->map[i][j], i, j);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_format_cub(char *file_name)
{
	char	*ext;

	ext = ft_strrchr(file_name, '.');
	if (!ext || ext == file_name)
		return (0);
	if (ft_strncmp(ext, ".cub", 5) != 0)
		return (0);
	return (1);
}

int ft_check_tiles(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' &&
				map[i][j] != 'N' && map[i][j] != 'S' &&
				map[i][j] != 'E' && map[i][j] != 'W' && !is_space(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int ft_check_elements(t_data *game)
{
	if (!game->no_texture || !game->so_texture || !game->we_texture || !game->ea_texture)
		return (mess_error(0, "Texture manquante"));
	if (game->floor_color == -1 || game->ceiling_color == -1)
		return (mess_error(0, "Couleur manquante"));
	return (1);
}

int ft_check_map(t_data *game, char *file_name)
{
	if (ft_check_format_cub(file_name) == 0)
		return (mess_error(0, "Format de fichier invalide"));
	if (ft_check_elements(game) == 0)
		return (0);
	if (ft_check_tiles(game->map) == 0)
		return (mess_error(0, "Caractères invalides dans la carte"));
	if (init_player(game) == 0)
		return (0);
	if (ft_check_walls(game) == 0)
		return (mess_error(0, "Murs invalides"));
	return (1);
}
