#include "../../inc/cub3d.h"

int	is_element_line(char *line)
{
	if (!line || !*line || is_space(line[0]))
		return (0);
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

bool	only_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t' || line[i] == '\n'
			|| line[i] == '\v' || line[i] == '\f'
			|| line[i] == '\r' || line[i] == ' ')
			i++;
		else
			return (false);
	}
	return (true);
}

int	is_valid_rgb(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && only_space(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}
