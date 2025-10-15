/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:17:53 by grohr             #+#    #+#             */
/*   Updated: 2025/10/09 14:08:59 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	*append_line_to_map_temp(char *map_temp, char *line)
{
	char	*temp;

	if (!map_temp)
		return (ft_strdup(line));
	temp = map_temp;
	map_temp = ft_strjoin(map_temp, line);
	free(temp);
	return (map_temp);
}

static char	*parse_map_lines(int fd, int *height, char *line)
{
	char	*map_temp;

	map_temp = NULL;
	while (line)
	{
		if (only_space(line))
		{
			free(line);
			free(map_temp);
			gnl_clear(fd);
			return (NULL);
		}
		map_temp = append_line_to_map_temp(map_temp, line);
		free(line);
		(*height)++;
		line = get_next_line(fd);
	}
	return (map_temp);
}

char	**ft_get_map(char *file_path, t_data *game)
{
	char	*map_temp;
	char	*line;
	int		fd;

	if (!open_and_parse_elements(file_path, game, &fd))
		return (NULL);
	line = get_first_map_line(fd);
	if (!line)
		return (NULL);
	map_temp = parse_map_lines(fd, &game->height_map, line);
	close(fd);
	gnl_clear(fd);
	if (!map_temp)
		return (NULL);
	game->map = ft_split(map_temp, '\n');
	free(map_temp);
	return (game->map);
}
