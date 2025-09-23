#include "../../inc/cub3d.h"

static double	setup_ray(t_data *data, int x, double *rx, double *ry)
{
	ray_dir(data, x, rx, ry);
	init_dda(data, *rx, *ry, &data->ray);
	dda_walk(data, &data->ray);
	return (dist_perp_wall(data, &data->ray, *rx, *ry));
}

static void	compute_line(t_data *data, t_column *col)
{
	col->line_h = (int)(data->screen.height / col->pdist);
	col->draw_start = -col->line_h / 2 + data->screen.height / 2;
	col->draw_end = col->line_h / 2 + data->screen.height / 2;
	col->y0c = col->draw_start;
	if (col->y0c < 0)
		col->y0c = 0;
	col->y1c = col->draw_end;
	if (col->y1c >= data->screen.height)
		col->y1c = data->screen.height - 1;
}

static void	compute_texture(t_data *data, t_column *col, double rx, double ry)
{
	double	hit_x;

	col->tex = wall_tex(data, &data->ray, rx, ry);
	if (data->ray.side == 0)
		hit_x = data->player.pos_y + col->pdist * ry;
	else
		hit_x = data->player.pos_x + col->pdist * rx;
	hit_x -= floor(hit_x);
	col->tex_x = (int)(hit_x * (double)col->tex->width);
	if (col->tex_x < 0)
		col->tex_x = 0;
	if (col->tex_x >= col->tex->width)
		col->tex_x = col->tex->width - 1;
	if ((data->ray.side == 0 && rx < 0) || (data->ray.side == 1 && ry > 0))
		col->tex_x = col->tex->width - col->tex_x - 1;
}

static void	draw_column(t_data *data, int x, t_column *col)
{
	int	y;

	y = 0;
	while (y < col->y0c)
	{
		draw_sky(data, x, y);
		y++;
	}
	draw_wall(data, x, col);
	y = col->y1c + 1;
	while (y < data->screen.height)
	{
		draw_floor(data, x, y);
		++y;
	}
}

int	render_frame(t_data *data)
{
	int			x;
	double		rx;
	double		ry;
	t_column	col;

	x = 0;
	while (x < data->screen.width)
	{
		col.pdist = setup_ray(data, x, &rx, &ry);
		compute_line(data, &col);
		compute_texture(data, &col, rx, ry);
		draw_column(data, x, &col);
		x++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->mlx.img_ptr, 0, 0);
	return (0);
}
