#include "../../inc/cub3d.h"

int mouse_move(int x, int y, t_data *data)
{
	double	delta_x;
	double	angle;
	double	old_dir_x;
	double	old_plane_x;
	(void)y;

	if (!data->mouse_rotating)
        return 0;
	delta_x = x - data->prev_mouse_x;
	angle = delta_x * data->mouse_sensitivity;
	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(angle) - data->player.dir_y *sin(angle);
	data->player.dir_y = old_dir_x * sin(angle) + data->player.dir_y * cos(angle);
	old_plane_x = data->player.plane_x;
    data->player.plane_x = data->player.plane_x * cos(angle) - data->player.plane_y * sin(angle);
    data->player.plane_y = old_plane_x * sin(angle) + data->player.plane_y * cos(angle);

    // Update previous mouse X
    data->prev_mouse_x = x;

    // Trigger redraw
    render_frame(data);
	return (0);
}

int mouse_press(int button, int x, int y, void *param)
{
    t_data *data = (t_data *)param;
    (void)x; (void)y;
    if (button == 1) // left click
        data->mouse_rotating = true;
    return 0;
}

int mouse_release(int button, int x, int y, void *param)
{
    t_data *data = (t_data *)param;
    (void)x; (void)y;
    if (button == 1)
        data->mouse_rotating = false;
    return 0;
}