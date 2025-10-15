/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:33:54 by grohr             #+#    #+#             */
/*   Updated: 2025/10/07 17:38:24 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	validate_texture_path(char *trimmed)
{
	char	*start;

	start = trimmed;
	while (*start)
	{
		if (ft_isdigit(*start) || *start == ',')
		{
			free(trimmed);
			return (mess_error(0, "Texture : caractères inattendus"));
		}
		start++;
	}
	if (!ft_strrchr(trimmed, '.')
		|| ft_strncmp(ft_strrchr(trimmed, '.'), ".xpm", 4) != 0)
	{
		free(trimmed);
		return (mess_error(0, "Extension de texture invalide (try .xpm)"));
	}
	return (1);
}

int	parse_texture(char *line, char **texture)
{
	char	*trimmed;

	if (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0)
		trimmed = ft_strtrim(line + 2, " \t\n");
	else
		trimmed = ft_strtrim(line + 3, " \t\n");
	if (!trimmed || !*trimmed)
	{
		free(trimmed);
		return (mess_error(0, "Chemin de texture vide ou invalide"));
	}
	if (!validate_texture_path(trimmed))
		return (0);
	*texture = trimmed;
	return (1);
}
