#include "../../inc/cub3d.h"

int	update(t_data *data)
{
	static long	last_time = 0;
	long		current_time;
	long		elapsed;

	current_time = get_time_ms();
	elapsed = current_time - last_time;
	if (elapsed < FRAME_TIME)
		return (0);
	last_time = current_time;
	move_player(data);
	rotate_player(data);
	render_frame(data);
	return (0);
}
