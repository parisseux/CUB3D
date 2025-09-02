#include "../../inc/cub3d.h"

// Dessine un carré sur la minimap à la position (x, y) avec la couleur donnée
static void draw_minimap_square(t_data *data, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			draw_pixel(&data->mlx, x + i, y + j, color, data);
			j++;
		}
		i++;
	}
}

// Dessine une ligne de pixels du point (x0, y0) au point (x1, y1) avec la couleur donnée
static void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1)
	{
		if (x0 >= 0 && x0 < data->screen.width && y0 >= 0 && y0 < data->screen.height)
			draw_pixel(&data->mlx, x0, y0, color, data);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

static void draw_fov(t_data *data)
{
	int i;
	double angle;
	double ray_pos_x, ray_pos_y;
	int pixel_x_start = MINIMAP_OFFSET_X + MINIMAP_SIZE / 2;
	int pixel_y_start = data->screen.height - MINIMAP_OFFSET_Y - MINIMAP_SIZE / 2;
	double fov = 0.66;
	int max_depth = MINIMAP_SIZE / MINIMAP_SCALE * 2;

	angle = atan2(data->player.dir_y, data->player.dir_x) - fov / 2;
	for (i = 0; i < MINIMAP_SIZE / 2; i++)
	{
		double current_angle = angle + i * (fov / (MINIMAP_SIZE / 2));
		double dir_x = cos(current_angle);
		double dir_y = sin(current_angle);
		ray_pos_x = data->player.pos_x;
		ray_pos_y = data->player.pos_y;

		int depth = 0;
		while (depth < max_depth)
		{
			int map_x = (int)ray_pos_x;
			int map_y = (int)ray_pos_y;

			if (map_y < 0 || map_y >= data->height_map ||
				map_x < 0 || map_x >= (int)ft_strlen(data->map[map_y]) ||
				data->map[map_y][map_x] == '1')
				break;

			ray_pos_x += dir_x * 0.1;
			ray_pos_y += dir_y * 0.1;
			depth++;
		}

		int pixel_x_end = pixel_x_start + (int)((ray_pos_x - data->player.pos_x) * MINIMAP_SCALE);
		int pixel_y_end = pixel_y_start + (int)((ray_pos_y - data->player.pos_y) * MINIMAP_SCALE);

		draw_line(data, pixel_x_start, pixel_y_start, pixel_x_end, pixel_y_end, MINIMAP_FOV_COLOR);
	}
}

// Dessine la minimap en bas à gauche
void draw_minimap(t_data *data)
{
	int i, j;
	int map_x = (int)data->player.pos_x - MINIMAP_SIZE / (2 * MINIMAP_SCALE);
	int map_y = (int)data->player.pos_y - MINIMAP_SIZE / (2 * MINIMAP_SCALE);
	int pixel_x, pixel_y;

	printf("Drawing minimap: screen (%d, %d), height_map %d\n",
		data->screen.width, data->screen.height, data->height_map);
	printf("Minimap map origin: (%d, %d), player pos: (%.2f, %.2f)\n",
		map_x, map_y, data->player.pos_x, data->player.pos_y);

	for (i = 0; i < MINIMAP_SIZE / MINIMAP_SCALE; i++)
	{
		for (j = 0; j < MINIMAP_SIZE / MINIMAP_SCALE; j++)
		{
			int map_i = map_y + i;
			int map_j = map_x + j;
			if (map_i >= 0 && map_i < data->height_map &&
				map_j >= 0 && data->map[map_i] &&
				map_j < (int)ft_strlen(data->map[map_i]))
			{
				pixel_x = MINIMAP_OFFSET_X + j * MINIMAP_SCALE;
				pixel_y = data->screen.height - MINIMAP_OFFSET_Y - MINIMAP_SIZE + i * MINIMAP_SCALE;
				if (data->map[map_i][map_j] == '1')
					draw_minimap_square(data, pixel_x, pixel_y, MINIMAP_WALL_COLOR);
				else
					draw_minimap_square(data, pixel_x, pixel_y, MINIMAP_FLOOR_COLOR);
			}
			// Aucun dessin hors-map => plus de fond noir
		}
	}

	// Dessiner le joueur au centre
	pixel_x = MINIMAP_OFFSET_X + MINIMAP_SIZE / 2;
	pixel_y = data->screen.height - MINIMAP_OFFSET_Y - MINIMAP_SIZE / 2;
	printf("Drawing player at pixel (%d, %d)\n", pixel_x, pixel_y);
	draw_minimap_square(data, pixel_x - MINIMAP_SCALE / 2, pixel_y - MINIMAP_SCALE / 2, MINIMAP_PLAYER_COLOR);

	// Dessiner le champ de vision
	draw_fov(data);
}
