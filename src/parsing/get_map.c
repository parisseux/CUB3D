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

bool only_space(char *line)
{
    int i;
    
    i = 0;
    while(line[i])
    {
        if (line[i]== '\t' || line[i] == '\n'
                || line[i] == '\v' || line[i] == '\f'
                || line[i] == '\r' || line[i] ==' ')
            i++;
        else
            return (false);
    }
    return (true);
}

char	**ft_get_map(char *file_path, t_data *game)
{
	char	*map_temp = NULL;
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
        if (only_space(line) == true)
        {
            free(line);
            free(map_temp);
            close(fd);
            return (NULL);
        }
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
