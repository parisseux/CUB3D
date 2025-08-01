#include "../../inc/cub3d.h"

static void move_direction(t_data *data, double dir_x, double dir_y)
{
    double new_x;
    double new_y;

    new_x = data->player.pos_x + dir_x * MOVE_SPEED;
    new_y = data->player.pos_y + dir_y * MOVE_SPEED;
    if (data->map[(int)new_y][(int)new_x] != '1')
    {
        data->player.pos_x = new_x;
        data->player.pos_y = new_y;
    }
}

void move_player(t_data *data)
{
    //printf("move_player: w=%d, s=%d, a=%d, d=%d\n", data->keys.w, data->keys.s, data->keys.a, data->keys.d);
    if (data->keys.w)
        move_direction(data, data->player.dir_x, data->player.dir_y);
    if (data->keys.s)
        move_direction(data, -data->player.dir_x, -data->player.dir_y);
    if (data->keys.a)
        move_direction(data, -data->player.plane_x, -data->player.plane_y);
    if (data->keys.d)
        move_direction(data, data->player.plane_x, data->player.plane_y);
}

void rotate_player(t_data *data)
{
    double old_dir_x;
    double old_plane_x;
    double cos_rot;
    double sin_rot;

    //printf("rotate_player: left=%d, right=%d\n", data->keys.left, data->keys.right);
    if (data->keys.left)
    {
        cos_rot = cos(-ROT_SPEED);
        sin_rot = sin(-ROT_SPEED);
        old_dir_x = data->player.dir_x;
        data->player.dir_x = old_dir_x * cos_rot - data->player.dir_y * sin_rot;
        data->player.dir_y = old_dir_x * sin_rot + data->player.dir_y * cos_rot;
        old_plane_x = data->player.plane_x;
        data->player.plane_x = old_plane_x * cos_rot - data->player.plane_y * sin_rot;
        data->player.plane_y = old_plane_x * sin_rot + data->player.plane_y * cos_rot;
    }
    if (data->keys.right)
    {
        cos_rot = cos(ROT_SPEED);
        sin_rot = sin(ROT_SPEED);
        old_dir_x = data->player.dir_x;
        data->player.dir_x = old_dir_x * cos_rot - data->player.dir_y * sin_rot;
        data->player.dir_y = old_dir_x * sin_rot + data->player.dir_y * cos_rot;
        old_plane_x = data->player.plane_x;
        data->player.plane_x = old_plane_x * cos_rot - data->player.plane_y * sin_rot;
        data->player.plane_y = old_plane_x * sin_rot + data->player.plane_y * cos_rot;
    }
}
