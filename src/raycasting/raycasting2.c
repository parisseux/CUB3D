#include "../../inc/cub3d.h"

// calcule la distance perpendiculaire du joeur au mur frappé par le rayon. 
//permet de dessiner la bonne hauteur du mur (projection perspective)
//va permettre de supprimer le fisheye
//side = 0 quand le rayon a frapper un mur vertical (Est/Ouest)
//side = 1 quand le rayon a frapper un mur horizontal (Nord/sud)
double dist_perp_wall(t_data *data, t_ray *ray, double rx, double ry)
{
	double dist;

	if (ray->side == 0)
		dist = (ray->map_x - data->player.pos_x + (1 - ray->step_x) * 0.5) / rx;
	else
		dist = (ray->map_y - data->player.pos_y + (1 - ray->step_y) * 0.5) / ry;
	if (dist < 1e-6)
		dist = 1e-6;
	return (dist > 0 ? dist : -dist);
}

//choisis quelle tecture de mur
t_texture* wall_tex(t_data *data, t_ray *ray, double rx, double ry)
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

void draw_wall(t_data *data, int x, t_column *col)
{
    int y;

    y = col->y0c;
    double step = (double)col->tex->height / (double)col->line_h;
    double tex_pos = (double)(col->y0c - col->draw_start) * step;

    while (y <= col->y1c)
    {
        int ty = (int)tex_pos;
        if (ty < 0) ty = 0;
        if (ty >= col->tex->height) ty = col->tex->height - 1;
        draw_pixel(x, y, color_tex(col->tex, col->tex_x, ty), data);
        tex_pos += step;
        y++;
    }
}
