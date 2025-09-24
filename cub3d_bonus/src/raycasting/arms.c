#include "../../inc/cub3d.h"

void draw_arm(t_data *data)
{
	int x;
	int y;
	int color;

	y = 0;
	while (y < data->arms.height)
	{
		x = 0;
		while (x < data->arms.width)
		{
			color = data->arms.pixels[y * data->arms.width + x];
			 if ((color & 0x00FFFFFF) != 0)
				draw_pixel( data->screen.width/2 - data->arms.width/2 + x,
						data->screen.height - data->arms.height + y,color,data);
			x++;
		}
		y++;
	}
}
