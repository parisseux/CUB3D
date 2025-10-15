/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:58:40 by grohr             #+#    #+#             */
/*   Updated: 2025/10/08 15:38:37 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Vérifie si c'est un chemin de texture valide (contient .xpm)
static int	is_valid_texture_path(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '.' && str[i + 1] == 'x'
			&& str[i + 2] == 'p' && str[i + 3] == 'm')
			return (1);
		i++;
	}
	return (0);
}

static int	parse_texture(char *line, char **texture)
{
	char	*trimmed;

	if (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0)
		trimmed = ft_strtrim(line + 2, " \t\n");
	else
		trimmed = ft_strtrim(line + 3, " \t\n");
	if (!trimmed || !*trimmed)
	{
		free(trimmed);
		return (0);
	}
	if ((ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0))
	{
		if (!is_valid_texture_path(trimmed))
		{
			free(trimmed);
			printf("Error: F and C must be texture paths (.xpm) in bonus\n");
			return (0);
		}
	}
	*texture = trimmed;
	return (1);
}

static int	is_element_line(char *line)
{
	if (!line || !*line || is_space(line[0]))
		return (0);
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

static int	parse_element_line(t_data *game, char *line, int *elements_found)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !game->no_texture)
		*elements_found += parse_texture(line, &game->no_texture);
	else if (ft_strncmp(line, "SO ", 3) == 0 && !game->so_texture)
		*elements_found += parse_texture(line, &game->so_texture);
	else if (ft_strncmp(line, "WE ", 3) == 0 && !game->we_texture)
		*elements_found += parse_texture(line, &game->we_texture);
	else if (ft_strncmp(line, "EA ", 3) == 0 && !game->ea_texture)
		*elements_found += parse_texture(line, &game->ea_texture);
	else if (ft_strncmp(line, "F ", 2) == 0 && !game->floor_texture)
		*elements_found += parse_texture(line, &game->floor_texture);
	else if (ft_strncmp(line, "C ", 2) == 0 && !game->sky_texture)
		*elements_found += parse_texture(line, &game->sky_texture);
	else
		return (mess_error(0, "Élément dup ou invalide"));
	return (1);
}

int	parse_elements(t_data *game, int fd)
{
	char	*line;
	int		elements_found;

	elements_found = 0;
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line && elements_found < 6)
	{
		if (is_element_line(line))
		{
			if (!parse_element_line(game, line, &elements_found))
			{
				free(line);
				gnl_clear(fd);
				return (0);
			}
		}
		if (elements_found == 6)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (elements_found == 6);
}
