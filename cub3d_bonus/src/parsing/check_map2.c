/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:58:47 by grohr             #+#    #+#             */
/*   Updated: 2025/10/08 14:58:47 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_check_border_map(char **map, int i, int j)
{
	if (i <= 0 || j <= 0 || !map[i + 1] || !map[i][j + 1])
		return (0);
	if (is_space(map[i - 1][j - 1]) || is_space(map[i - 1][j])
		|| is_space(map[i - 1][j + 1]))
		return (0);
	if (map[i - 1][j] == '\0' || map[i + 1][j] == '\0')
		return (0);
	if (is_space(map[i][j - 1]) || is_space(map[i][j + 1]))
		return (0);
	if (map[i][j - 1] == '\0' || map[i][j + 1] == '\0')
		return (0);
	if (is_space(map[i + 1][j - 1]) || is_space(map[i + 1][j])
		|| is_space(map[i + 1][j + 1]))
		return (0);
	return (1);
}
