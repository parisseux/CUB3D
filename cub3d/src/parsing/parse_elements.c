/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:12:08 by pchatagn          #+#    #+#             */
/*   Updated: 2025/10/07 17:33:19 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Skip whitespaces (au cas où, même si trimmed)
// Optionnel + ou - (exactement un signe)
// Si un autre signe suit, c'est invalide (ex: ++60, --60)
// Doit avoir au moins un digit
// Check que le reste est seulement digits
static int	is_valid_number(char *str)
{
	int	i;
	int	has_digit;

	if (!str || !*str)
		return (0);
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '+' || str[i] == '-')
		return (0);
	if (!ft_isdigit(str[i]))
		return (0);
	has_digit = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		has_digit = 1;
		i++;
	}
	return (has_digit);
}

static int	validate_rgb_values(char **rgb, int col[3])
{
	int	i;

	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_free_split(rgb);
		return (0);
	}
	i = 0;
	while (i < 3)
	{
		if (!is_valid_number(rgb[i]))
		{
			ft_free_split(rgb);
			return (0);
		}
		col[i] = ft_atoi(rgb[i]);
		i++;
	}
	return (1);
}

static int	parse_color(char *line, int *color)
{
	char	*trimmed;
	char	**rgb;
	int		col[3];

	trimmed = ft_strtrim(line + 2, " \t\n");
	if (!trimmed)
		return (0);
	rgb = ft_split(trimmed, ',');
	free(trimmed);
	if (!validate_rgb_values(rgb, col) || !is_valid_rgb(col[0], col[1], col[2]))
		return (0);
	*color = (col[0] << 16) | (col[1] << 8) | col[2];
	ft_free_split(rgb);
	return (1);
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
	else if (ft_strncmp(line, "F ", 2) == 0 && game->floor_color == -1)
		*elements_found += parse_color(line, &game->floor_color);
	else if (ft_strncmp(line, "C ", 2) == 0 && game->ceiling_color == -1)
		*elements_found += parse_color(line, &game->ceiling_color);
	else
		return (mess_error(0, "Élément dup ou invalide"));
	return (1);
}

//is_element_line : in parsing_utils.c
int	parse_elements(t_data *game, int fd)
{
	char	*line;
	int		elements_found;

	elements_found = 0;
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 0);
	while (line && elements_found < 6)
	{
		if (is_element_line(line))
		{
			if (!parse_element_line(game, line, &elements_found))
				return (free(line), gnl_clear(fd), close(fd), 0);
		}
		if (elements_found == 6)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (elements_found == 6);
}
