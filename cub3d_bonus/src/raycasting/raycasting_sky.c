/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_sky.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:22:41 by grohr             #+#    #+#             */
/*   Updated: 2025/10/07 17:22:42 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_sky(t_data *data, t_sky *sky, int x)
{
	sky->camera_x = 2.0 * x / data->screen.width - 1.0;
	sky->dir_x = data->player.dir_x + data->player.plane_x * sky->camera_x;
	sky->dir_y = data->player.dir_y + data->player.plane_y * sky->camera_x;
	sky->angle = atan2(sky->dir_y, sky->dir_x);
	sky->scale = data->sky_scale;
	sky->offset = data->sky_offset * data->tex_sky.width;
}

void	draw_sky(t_data *data, int x, int y)
{
	t_sky	sky;
	int		tex_x;
	int		tex_y;

	init_sky(data, &sky, x);
	tex_x = (int)((((sky.angle + M_PI) / (2 * M_PI))
				* data->tex_sky.width * sky.scale) + sky.offset);
	tex_x = (tex_x % data->tex_sky.width + data->tex_sky.width)
		% data->tex_sky.width;
	tex_y = (int)(((double)y / data->screen.height)
			* data->tex_sky.height * sky.scale);
	tex_y = (tex_y % data->tex_sky.height + data->tex_sky.height)
		% data->tex_sky.height;
	draw_pixel(x, y, get_tex_color(&data->tex_sky, tex_x, tex_y), data);
}
