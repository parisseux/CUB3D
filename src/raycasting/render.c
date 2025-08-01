#include "../../inc/cub3d.h"

static void get_wall_dir(t_ray *ray, double ray_x, double ray_y, t_data *data, t_texture **tex)
{
    if (ray->side == 0)
    {
        if (ray_x > 0)
            *tex = &data->tex_east;
        else
            *tex = &data->tex_west;
    }
    else
    {
        if (ray_y > 0)
            *tex = &data->tex_south;
        else
            *tex = &data->tex_north;
    }
}

static int get_tex_color(t_texture *tex, int tex_x, int tex_y)
{
    char *dst;
    int color;

    if (!tex->data)
    {
        printf("Error: Texture data is NULL\n");
        return (0xFF0000); // Rouge par défaut
    }
    if (tex_x >= 0 && tex_x < tex->width && tex_y >= 0 && tex_y < tex->height)
    {
        dst = tex->data + (tex_y * tex->size_line + tex_x * (tex->bpp / 8));
        if (tex->endian == 0)
        {
            // Little-endian: ARGB
            unsigned char *pixel = (unsigned char *)dst;
            color = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
        }
        else
        {
            // Big-endian: RGBA
            color = *(unsigned int *)dst;
        }
        if (color == 0)
        {
            printf("Warning: Black pixel at (%d,%d), forcing red\n", tex_x, tex_y);
            color = 0xFF0000;
        }
        //printf("get_tex_color: tex_x=%d, tex_y=%d, color=0x%X\n", tex_x, tex_y, color);
    }
    else
    {
        color = 0x808080; // Gris par défaut
        printf("Out of bounds: tex_x=%d, tex_y=%d, width=%d, height=%d\n", tex_x, tex_y, tex->width, tex->height);
    }
    return (color);
}

void draw_column(t_data *data, int x, int start, int end, t_texture *tex)
{
    int y;
    int tex_x;
    int tex_y;
    double wall_x;

    y = 0;
    wall_x = data->player.pos_x + data->ray.perp_dist * data->ray.delta_dist_x;
    if (data->ray.side == 1)
        wall_x = data->player.pos_y + data->ray.perp_dist * data->ray.delta_dist_y;
    wall_x -= (int)wall_x;
    tex_x = (int)(wall_x * (double)tex->width);
    if ((data->ray.side == 0 && data->ray.delta_dist_x < 0) || (data->ray.side == 1 && data->ray.delta_dist_y > 0))
        tex_x = tex->width - tex_x - 1;
    //printf("draw_column: x=%d, start=%d, end=%d, tex_x=%d, wall_x=%f\n", x, start, end, tex_x, wall_x);
    while (y < WINDOW_HEIGHT)
    {
        if (y < start)
            draw_pixel(&data->mlx, x, y, data->ceiling_color);
        else if (y >= start && y <= end)
        {
            tex_y = (int)((y - start) * tex->height / (end - start + 1));
            draw_pixel(&data->mlx, x, y, get_tex_color(tex, tex_x, tex_y));
        }
        else
            draw_pixel(&data->mlx, x, y, data->floor_color);
        y++;
    }
}

static void init_ray(t_data *data, int x, double *ray_x, double *ray_y)
{
    double camera_x;

	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	*ray_x = data->player.dir_x + data->player.plane_x * camera_x;
	*ray_y = data->player.dir_y + data->player.plane_y * camera_x;
}

static void setup_ray(t_data *data, double ray_x, double ray_y, t_ray *ray)
{
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
	ray->delta_dist_x = fabs(1 / ray_x);
	ray->delta_dist_y = fabs(1 / ray_y);
	if (ray_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.pos_x) * ray->delta_dist_x;
	}
	if (ray_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.pos_y) * ray->delta_dist_y;
	}
}

static void cast_ray(t_data *data, t_ray *ray)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void calc_wall(t_ray *ray, int *start, int *end)
{
    int height;

	if (ray->side == 0)
		ray->perp_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_dist = (ray->side_dist_y - ray->delta_dist_y);
	height = (int)(WINDOW_HEIGHT / ray->perp_dist);
	*start = -height / 2 + WINDOW_HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	*end = height / 2 + WINDOW_HEIGHT / 2;
	if (*end >= WINDOW_HEIGHT)
		*end = WINDOW_HEIGHT - 1;
}

int render_frame(t_data *data)
{
    int x;
    double ray_x;
    double ray_y;
    t_texture *tex;
    int start;
    int end;

    data->ray.hit = 0;
    x = 0;
    while (x < WINDOW_WIDTH)
    {
        init_ray(data, x, &ray_x, &ray_y);
        setup_ray(data, ray_x, ray_y, &data->ray);
        cast_ray(data, &data->ray);
        calc_wall(&data->ray, &start, &end);
        get_wall_dir(&data->ray, ray_x, ray_y, data, &tex);
        draw_column(data, x, start, end, tex);
        x++;
    }
    mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img_ptr, 0, 0);
    return (0);
}
