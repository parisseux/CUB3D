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

char	*append_line_to_map_temp(char *map_temp, char *line)
{
	char	*temp;

	if (!map_temp)
		return (ft_strdup(line));
	temp = map_temp;
	map_temp = ft_strjoin(map_temp, line);
	free(temp);
	return (map_temp);
}

char *parse_map_lines(int fd, int *height, char *line)
{
    char *map_temp;

    map_temp = NULL;
	while (line)
	{
		if (only_space(line))
		{
			free(map_temp);
			return (NULL);
		}
		map_temp = append_line_to_map_temp(map_temp, line);
		free(line);
		(*height)++;
		line = get_next_line(fd);
	}
	return (map_temp);
}

char **ft_get_map(char*file_path, t_data *game)
{
    char	*map_temp;
	int fd;
	char *line;

    fd =  open(file_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!parse_elements(game, fd))
		return (NULL);
    line = get_next_line(fd);
    while (line && only_space(line))
    {
        free(line);
        line = get_next_line(fd);
    }
	if (!line || start_of_map(line) == false)
    {
        free(line);
        close(fd);
        return (NULL);
    }
    map_temp = parse_map_lines(fd, &game->height_map, line);
    close(fd);
    if (!map_temp)
        return (NULL);
    game->map = ft_split(map_temp, '\n');
    free(map_temp);
    return(game->map);
}
