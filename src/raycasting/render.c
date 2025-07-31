#include "../../inc/cub3d.h"

#define WINDOW_WIDTH    1280
#define WINDOW_HEIGHT   720

void    draw_column(t_data *data, int x, int start, int end)
{
    int     y;
    int     color;

    y = 0;
    color = 0x808080;
    while (y < WINDOW_HEIGHT)
    {
        if (y < start)
            draw_pixel(&data->mlx, x, y, data->ceiling_color);
        else if (y >= start && y <= end)
            draw_pixel(&data->mlx, x, y, color);
        else
            draw_pixel(&data->mlx, x, y, data->floor_color);
        y++;
    }
}

static void init_ray(t_data *data, int x, double *ray_x, double *ray_y)
{
    double  camera_x;

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
    int     height;

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
    int     x;
    double  ray_x;
    double  ray_y;
    t_ray   ray;
    int     start;
    int     end;

    move_player(data);
    rotate_player(data);
    x = 0;
    while (x < WINDOW_WIDTH)
    {
        init_ray(data, x, &ray_x, &ray_y);
        setup_ray(data, ray_x, ray_y, &ray);
        cast_ray(data, &ray);
        calc_wall(&ray, &start, &end);
        draw_column(data, x, start, end);
        x++;
    }
    mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img_ptr, 0, 0);
    return (0);
}
