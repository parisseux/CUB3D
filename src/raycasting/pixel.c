#include "../../inc/cub3d.h"

#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	720

void	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = mlx->img_data + (y * mlx->size_line + x * (mlx->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
