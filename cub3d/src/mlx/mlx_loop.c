#include "../../inc/cub3d.h"

int	update(t_data *data)
{
	move_player(data);
	rotate_player(data);
	render_frame(data);
	return (0);
}
