/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:19:25 by grohr             #+#    #+#             */
/*   Updated: 2025/10/07 17:21:09 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	calc_move_speed(t_data *data)
{
	return (BASE_MOVE_SPEED * (data->screen.width / REFERENCE_WIDTH));
}

double	calc_rot_speed(t_data *data)
{
	return (BASE_ROT_SPEED * (data->screen.width / REFERENCE_WIDTH));
}

int	pixel_skip(t_data *data)
{
	if (data->screen.width > 1600)
		return (2);
	return (1);
}

t_vec	rotate_vec(double x, double y, double angle)
{
	t_vec	res;

	res.x = x * cos(angle) - y * sin(angle);
	res.y = x * sin(angle) + y * cos(angle);
	return (res);
}

double	dabs(double x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}
