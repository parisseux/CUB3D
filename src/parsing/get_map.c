#include "../../inc/cub3d.h"

bool	start_of_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (line[i] != '1')
			return (false);
		else if (line[i] == '1')
			break;
	}
	return (true);
}

char	*ft_read_and_join(t_data *game)
{
	char	*line;
	char	*map_temp;
	char	*temp;
	int		height;

	height = 0;
	map_temp = NULL;
	line = get_next_line(game->fd_map);
	while (line && start_of_map(line) == false)
	{
		free(line);
		line = get_next_line(game->fd_map);
	}
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
		height++;
		line = get_next_line(game->fd_map);
	}
	game->height_map = height;
	return (map_temp);
}

char	**ft_get_map(char *file_path, t_data *game)
{
	char	*map_temp;

	if (!parse_elements(game, file_path))
	{
		perror("Error");
		exit(1);
	}
	game->fd_map = open(file_path, O_RDONLY);
	if (game->fd_map < 0)
	{
		perror("Error");
		exit(1);
	}
	map_temp = ft_read_and_join(game);
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
