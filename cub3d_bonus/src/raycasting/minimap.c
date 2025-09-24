#include "../../inc/cub3d.h"

static void draw_rect(t_data *data, int x, int y, int size, int color)
{
	int i;
	int j;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			draw_pixel(x + i, y + j, color, data);
			j++;
		}
		i++;
	}
}

static void draw_player(t_data *data)
{
	int px;
	int py;

	px = MINIMAP_MARGIN + (int)(data->player.pos_x * MINIMAP_SCALE);
	py = MINIMAP_MARGIN + (int)(data->player.pos_y * MINIMAP_SCALE);
	draw_rect(data, px - PLAYER_SIZE, py - PLAYER_SIZE, PLAYER_SIZE * 2,  0xFF0000);
}

void draw_minimap(t_data *data)
{
	int i;
	int j;
	int start_x;
	int start_y;

	start_x = MINIMAP_MARGIN;
	start_y = MINIMAP_MARGIN;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while(data->map[i][j])
		{
			if (data->map[i][j] == '1')
				draw_rect(data, start_x + j * MINIMAP_SCALE,
				start_y + i * MINIMAP_SCALE, MINIMAP_SCALE, 0x000022);
			else if (data->map[i][j] == '0')
					draw_rect(data, start_x + j * MINIMAP_SCALE,
					start_y + i * MINIMAP_SCALE, MINIMAP_SCALE, 0x808080);
			j++;
		}
		i++;
	}
	draw_player(data);
}
