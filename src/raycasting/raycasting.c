#include "../../inc/cub3d.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define MOVE_SPEED 0.04
#define ROT_SPEED 0.015

void put_pixel_to_image(t_mlx *mlx, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        dst = mlx->img_data + (y * mlx->size_line + x * (mlx->bpp / 8));
        *(unsigned int *)dst = color;
    }
}

void init_camera(t_data *game)
{
    if (game->player.orientation == 'N')
    {
        game->player.dir_x = 0;
        game->player.dir_y = -1;
        game->player.plane_x = 0.66; // Champ de vision (FOV) ~66°
        game->player.plane_y = 0;
    }
    else if (game->player.orientation == 'S')
    {
        game->player.dir_x = 0;
        game->player.dir_y = 1;
        game->player.plane_x = -0.66;
        game->player.plane_y = 0;
    }
    else if (game->player.orientation == 'E')
    {
        game->player.dir_x = 1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = 0.66;
    }
    else if (game->player.orientation == 'W')
    {
        game->player.dir_x = -1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = -0.66;
    }
    game->keys.w = 0;
    game->keys.s = 0;
    game->keys.a = 0;
    game->keys.d = 0;
    game->keys.left = 0;
    game->keys.right = 0;
}

static void move_player(t_data *game)
{
    double new_x;
    double new_y;

    if (game->keys.w)
    {
        new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
        new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
        if (game->map[(int)new_y][(int)new_x] != '1')
        {
            game->player.pos_x = new_x;
            game->player.pos_y = new_y;
        }
    }
    if (game->keys.s)
    {
        new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
        new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
        if (game->map[(int)new_y][(int)new_x] != '1')
        {
            game->player.pos_x = new_x;
            game->player.pos_y = new_y;
        }
    }
    if (game->keys.a)
    {
        new_x = game->player.pos_x - game->player.plane_x * MOVE_SPEED;
        new_y = game->player.pos_y - game->player.plane_y * MOVE_SPEED;
        if (game->map[(int)new_y][(int)new_x] != '1')
        {
            game->player.pos_x = new_x;
            game->player.pos_y = new_y;
        }
    }
    if (game->keys.d)
    {
        new_x = game->player.pos_x + game->player.plane_x * MOVE_SPEED;
        new_y = game->player.pos_y + game->player.plane_y * MOVE_SPEED;
        if (game->map[(int)new_y][(int)new_x] != '1')
        {
            game->player.pos_x = new_x;
            game->player.pos_y = new_y;
        }
    }
}

static void rotate_player(t_data *game)
{
    double old_dir_x;
    double old_plane_x;
    double cos_rot;
    double sin_rot;

    if (game->keys.left)
    {
        cos_rot = cos(-ROT_SPEED);
        sin_rot = sin(-ROT_SPEED);
        old_dir_x = game->player.dir_x;
        game->player.dir_x = old_dir_x * cos_rot - game->player.dir_y * sin_rot;
        game->player.dir_y = old_dir_x * sin_rot + game->player.dir_y * cos_rot;
        old_plane_x = game->player.plane_x;
        game->player.plane_x = old_plane_x * cos_rot - game->player.plane_y * sin_rot;
        game->player.plane_y = old_plane_x * sin_rot + game->player.plane_y * cos_rot;
    }
    if (game->keys.right)
    {
        cos_rot = cos(ROT_SPEED);
        sin_rot = sin(ROT_SPEED);
        old_dir_x = game->player.dir_x;
        game->player.dir_x = old_dir_x * cos_rot - game->player.dir_y * sin_rot;
        game->player.dir_y = old_dir_x * sin_rot + game->player.dir_y * cos_rot;
        old_plane_x = game->player.plane_x;
        game->player.plane_x = old_plane_x * cos_rot - game->player.plane_y * sin_rot;
        game->player.plane_y = old_plane_x * sin_rot + game->player.plane_y * cos_rot;
    }
}

int key_press(int keycode, t_data *game)
{
    if (keycode == 53 || keycode == 65307) // ESC
    {
        cleanup(game);
        exit(0);
    }
    if (keycode == 13 || keycode == 119) // W
        game->keys.w = 1;
    if (keycode == 1 || keycode == 115) // S
        game->keys.s = 1;
    if (keycode == 0 || keycode == 97) // A
        game->keys.a = 1;
    if (keycode == 2 || keycode == 100) // D
        game->keys.d = 1;
    if (keycode == 123 || keycode == 65361) // Flèche gauche
        game->keys.left = 1;
    if (keycode == 124 || keycode == 65363) // Flèche droite
        game->keys.right = 1;
    return (0);
}

int key_release(int keycode, t_data *game)
{
    if (keycode == 13 || keycode == 119) // W
        game->keys.w = 0;
    if (keycode == 1 || keycode == 115) // S
        game->keys.s = 0;
    if (keycode == 0 || keycode == 97) // A
        game->keys.a = 0;
    if (keycode == 2 || keycode == 100) // D
        game->keys.d = 0;
    if (keycode == 123 || keycode == 65361) // Flèche gauche
        game->keys.left = 0;
    if (keycode == 124 || keycode == 65363) // Flèche droite
        game->keys.right = 0;
    return (0);
}

static void draw_column(t_data *game, int x, int draw_start, int draw_end, int color)
{
    int y;

    y = 0;
    while (y < WINDOW_HEIGHT)
    {
        if (y < draw_start)
            put_pixel_to_image(&game->mlx, x, y, game->ceiling_color);
        else if (y >= draw_start && y <= draw_end)
            put_pixel_to_image(&game->mlx, x, y, color);
        else
            put_pixel_to_image(&game->mlx, x, y, game->floor_color);
        y++;
    }
}

int render_frame(t_data *game)
{
    int x;
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    int step_x;
    int step_y;
    int hit;
    int side;
    double perp_wall_dist;
    int line_height;
    int draw_start;
    int draw_end;

    move_player(game);
    rotate_player(game);
    x = 0;
    while (x < WINDOW_WIDTH)
    {
        camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
        ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
        ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
        map_x = (int)game->player.pos_x;
        map_y = (int)game->player.pos_y;
        delta_dist_x = fabs(1 / ray_dir_x);
        delta_dist_y = fabs(1 / ray_dir_y);
        hit = 0;
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (game->player.pos_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->player.pos_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (game->player.pos_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->player.pos_y) * delta_dist_y;
        }
        while (!hit)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (game->map[map_y][map_x] == '1')
                hit = 1;
        }
        if (side == 0)
            perp_wall_dist = (side_dist_x - delta_dist_x);
        else
            perp_wall_dist = (side_dist_y - delta_dist_y);
        line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
        draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_end >= WINDOW_HEIGHT)
            draw_end = WINDOW_HEIGHT - 1;
        draw_column(game, x, draw_start, draw_end, 0x808080); // Gris pour les murs
        x++;
    }
    mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->mlx.img_ptr, 0, 0);
    return (0);
}
