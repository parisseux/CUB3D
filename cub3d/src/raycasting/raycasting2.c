/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:18:23 by grohr             #+#    #+#             */
/*   Updated: 2025/10/07 17:18:24 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// calcule la distance perpendiculaire du joeur au mur frappé par le rayon. 
//permet de dessiner la bonne hauteur du mur (projection perspective)
//va permettre de supprimer le fisheye
//side = 0 quand le rayon a frapper un mur vertical (Est/Ouest)
//side = 1 quand le rayon a frapper un mur horizontal (Nord/sud)
double	dist_perp_wall(t_data *data, t_ray *ray, double rx, double ry)
{
	double	dist;

	if (ray->side == 0)
		dist = (ray->map_x - data->player.pos_x + (1 - ray->step_x) * 0.5) / rx;
	else
		dist = (ray->map_y - data->player.pos_y + (1 - ray->step_y) * 0.5) / ry;
	if (dist < 1e-6)
		dist = 1e-6;
	if (dist > 0)
		return (dist);
	else
		return (-dist);
}

t_texture	*wall_tex(t_data *data, t_ray *ray, double rx, double ry)
{
	if (ray->side == 0)
	{
		if (rx > 0)
			return (&data->tex_east);
		else
			return (&data->tex_west);
	}
	else
	{
		if (ry > 0)
			return (&data->tex_south);
		else
			return (&data->tex_north);
	}
}

void	draw_ceiling_floor(t_data *data, int y0, int y1, int x)
{
	int	y;

	if (y0 < 0)
		y0 = 0;
	if (y1 >= data->screen.height)
		y1 = data->screen.height - 1;
	y = 0;
	while (y < y0)
	{
		draw_pixel(x, y, data->ceiling_color, data);
		y++;
	}
	y = y1 + 1;
	while (y < data->screen.height)
	{
		draw_pixel(x, y, data->floor_color, data);
		y++;
	}
}

void	draw_wall(t_data *data, int x, t_column *col)
{
	int		y;
	double	step;
	double	tex_pos;
	int		ty;

	y = col->y0c;
	step = (double)col->tex->height / (double)col->line_h;
	tex_pos = (double)(col->y0c - col->draw_start) * step;
	while (y <= col->y1c)
	{
		ty = (int)tex_pos;
		if (ty < 0)
			ty = 0;
		if (ty >= col->tex->height)
			ty = col->tex->height - 1;
		draw_pixel(x, y, color_tex(col->tex, col->tex_x, ty), data);
		tex_pos += step;
		y++;
	}
}

void	ray_dir(t_data *data, int x, double *rx, double *ry)
{
	double	camera_x;

	camera_x = (2.0 * x) / (double)data->screen.width - 1.0;
	*rx = data->player.dir_x + data->player.plane_x * camera_x;
	*ry = data->player.dir_y + data->player.plane_y * camera_x;
}
