
#include "cub3d.h"

int	ft_check_map(t_data *game, char *file_name)
{
	if (ft_check_format_cub(file_name) == 0)
		return (0);
	if (ft_check_tiles(game) == 0)
		return (0);
	return (1);
}

char	*ft_read_and_join(int fd)
{
	char	*line;
	char	*map_temp;
	char	*temp;

	map_temp = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (map_temp == NULL)
			map_temp = ft_strdup(line);
		else
		{
			temp = map_temp;
			map_temp = ft_strjoin(map_temp, line);
			free(temp);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (map_temp);
}

char	**ft_get_map(char *file_path, t_data *game)
{
	char	*map_temp;

	game->fd_map = open(file_path, O_RDONLY);
	if (game->fd_map < 0)
    {
        perror("Error");
        exit (1);
    }
	map_temp = ft_read_and_join(game->fd_map);
	close(game->fd_map);
    if (!map_temp)
    {
        perror("Error");
        exit(1);
    }
	game->map = ft_split(map_temp, '\n');
	free(map_temp);
	return (game->map);
}
