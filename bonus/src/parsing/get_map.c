#include "../../inc/cub3d.h"

bool	start_of_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (line[i] == '1')
			return (true);
		else
			return (false);
	}
	return (false);
}

// char	*ft_read_and_join(t_data *game)
// {
// 	char	*line;
// 	char	*map_temp;
// 	char	*temp;
// 	int		height;

// 	height = 0;
// 	map_temp = NULL;
// 	line = get_next_line(game->fd_map);
// 	while (line && start_of_map(line) == false)
// 	{
// 		free(line);
// 		line = get_next_line(game->fd_map);
// 	}
// 	printf("line: %s\n", line);
// 	while (line && start_of_map(line) == true)
// 	{
// 		if (map_temp == NULL)
// 			map_temp = ft_strdup(line);
// 		else
// 		{
// 			temp = map_temp;
// 			map_temp = ft_strjoin(map_temp, line);
// 			free(temp);
// 		}
// 		free(line);
// 		height++;
// 		line = get_next_line(game->fd_map);
// 	}
// 	game->height_map = height;
// 	return (map_temp);
// }

char	**ft_get_map(char *file_path, t_data *game)
{
	char	*map_temp;
	int fd;
	char *line;
    char *temp;
    int height = 0;

	fd =  open(file_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	
	if (!parse_elements(game, fd))
	{
		close(fd);
		return (NULL);
	}
	line = get_next_line(fd);
	while (line && start_of_map(line) == false)
    {
        free(line);
        line = get_next_line(fd);
    }

    while (line)
    {
        if (!map_temp)
            map_temp = ft_strdup(line);
        else
        {
            temp = map_temp;
            map_temp = ft_strjoin(map_temp, line);
            free(temp);
        }
        free(line);
        height++;
        line = get_next_line(fd);
    }
    close(fd);

    game->height_map = height;
    if (!map_temp)
        return (NULL);

    game->map = ft_split(map_temp, '\n');
    free(map_temp);

    return (game->map);
}
