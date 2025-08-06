#include "../../inc/cub3d.h"

void	draw_pixel(t_mlx *mlx, int x, int y, int color, t_data *data)
{
	char	*dst;

	if (x >= 0 && x < data->screen.width && y >= 0 && y < data->screen.height)
	{
		dst = mlx->img_data + (y * mlx->size_line + x * (mlx->bpp / 8));
		*(unsigned int *)dst = color;
	}
}