/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:22:50 by grohr             #+#    #+#             */
/*   Updated: 2025/10/07 17:22:51 by grohr            ###   ########.fr       */
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

int	get_tex_color(t_texture *tex, int tex_x, int tex_y)
{
	char			*dst;
	int				color;
	unsigned char	*pixel;

	if (!tex->data)
		return (0xFF0000);
	if (tex_x >= 0 && tex_x < tex->width && tex_y >= 0 && tex_y < tex->height)
	{
		dst = tex->data + (tex_y * tex->size_line + tex_x * (tex->bpp / 8));
		if (tex->endian == 0)
		{
			pixel = (unsigned char *)dst;
			color = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
		}
		else
			color = *(unsigned int *)dst;
		if (color == 0)
			color = 0xFF0000;
	}
	else
		color = 0x808080;
	return (color);
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
