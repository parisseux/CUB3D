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

//couleur de texture 
int color_tex(t_texture *tex, int tx, int ty)
{
	const char *p;
	const unsigned char *px;

	if (!tex->data)
		return (0xFF0000);
	if (tx < 0 || tx >= tex->width || ty < 0 || ty >= tex->height)
		return (0x808080);
	p = tex->data + (ty * tex->size_line + tx * (tex->bpp / 8));
	if (tex->endian == 0)
	{
		px = (const unsigned char *)p;
		return (px[2] << 16) | (px[1] << 8) | px[0];
	}
	return *(const unsigned int*)p;
}