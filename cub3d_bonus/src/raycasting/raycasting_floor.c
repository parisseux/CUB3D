/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_floor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:22:38 by grohr             #+#    #+#             */
/*   Updated: 2025/10/07 17:22:39 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_floor(t_data *data, t_floor *floor, int y, int x)
{
	floor->pos_x = data->player.pos_x;
	floor->pos_y = data->player.pos_y;
	floor->dir_x = data->player.dir_x;
	floor->dir_y = data->player.dir_y;
	floor->plane_x = data->player.plane_x;
	floor->plane_y = data->player.plane_y;
	floor->denom = (y - data->screen.height / 2.0);
	if (floor->denom == 0.0)
		floor->denom = 1.0;
	floor->row_distance = (data->screen.height / 2.0) / floor->denom;
	floor->cam = 2.0 * x / (double)data->screen.width - 1.0;
	floor->floor_x = floor->pos_x + floor->row_distance
		* (floor->dir_x + floor->plane_x * floor->cam);
	floor->floor_y = floor->pos_y + floor->row_distance
		* (floor->dir_y + floor->plane_y * floor->cam);
}

void	draw_floor(t_data *data, int x, int y)
{
	t_floor	floor;
	int		tex_x;
	int		tex_y;

	init_floor(data, &floor, y, x);
	tex_x = (int)(floor.floor_x * data->tex_floor.width);
	tex_y = (int)(floor.floor_y * data->tex_floor.height);
	tex_x = (tex_x % data->tex_floor.width + data->tex_floor.width)
		% data->tex_floor.width;
	tex_y = (tex_y % data->tex_floor.height + data->tex_floor.height)
		% data->tex_floor.height;
	draw_pixel(x, y, get_tex_color(&data->tex_floor, tex_x, tex_y), data);
}
