/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:44:33 by grohr             #+#    #+#             */
/*   Updated: 2025/10/09 14:08:38 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	start_of_map(char *line)
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

int	open_and_parse_elements(char *file_path, t_data *game, int *fd)
{
	*fd = open(file_path, O_RDONLY);
	if (*fd < 0)
		return (0);
	if (!parse_elements(game, *fd))
	{
		gnl_clear(*fd);
		close(*fd);
		return (0);
	}
	return (1);
}

char	*get_first_map_line(int fd)
{
	char	*line;

	line = skip_empty_lines(fd);
	if (!line || !start_of_map(line))
	{
		if (line)
			free(line);
		gnl_clear(fd);
		close(fd);
		return (NULL);
	}
	return (line);
}
