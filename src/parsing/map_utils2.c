#include "cub3d.h"

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

int is_space(char c)
{
    if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c ==' ')
        return (1);
    else 
        return (0);

}

int	ft_check_tiles(t_data *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] != '1' && game->map[i][j] != '0'
					&& game->map[i][j] != 'N' && game->map[i][j] != 'S' &&
					game->map[i][j] != 'E' && game->map[i][j] != 'W' && !is_space(game->map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
