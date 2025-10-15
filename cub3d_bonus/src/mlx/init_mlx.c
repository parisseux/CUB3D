/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:18:44 by grohr             #+#    #+#             */
/*   Updated: 2025/10/13 14:43:27 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	get_screen_size(t_data *data)
{
	t_resolution_profile	profiles[5];
	int						profile_index;

	profiles[0] = (t_resolution_profile){"tryhard", 800, 600,
		"Performance max"};
	profiles[1] = (t_resolution_profile){"balanced", 1280, 720, "Balanced"};
	profiles[2] = (t_resolution_profile){"quality", 1440, 900,
		"Deustsche qualität"};
	profiles[3] = (t_resolution_profile){"mid-screen-linux", 1920, 1080,
		"Linux mid"};
	profiles[4] = (t_resolution_profile){"full-screen-linux", 3840, 2160,
		"Taille pc école, lag de fou"};
	profile_index = 3;
	data->screen.width = profiles[profile_index].width;
	data->screen.height = profiles[profile_index].height;
}

static int	load_texture(t_data *data, t_texture *tex, char *path)
{
	int	width;
	int	height;

	tex->img_ptr = mlx_xpm_file_to_image(data->mlx.mlx_ptr, path, &width,
			&height);
	if (!tex->img_ptr)
	{
		printf("Error: Failed to load image %s\n", path);
		return (0);
	}
	tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->size_line,
			&tex->endian);
	if (!tex->data)
	{
		printf("Error: Failed to get texture data for %s\n", path);
		mlx_destroy_image(data->mlx.mlx_ptr, tex->img_ptr);
		tex->img_ptr = NULL;
		return (0);
	}
	tex->width = width;
	tex->height = height;
	return (1);
}

static int	load_all_textures(t_data *data)
{
	if (!load_texture(data, &data->tex_north, data->no_texture)
		|| !load_texture(data, &data->tex_south, data->so_texture)
		|| !load_texture(data, &data->tex_west, data->we_texture)
		|| !load_texture(data, &data->tex_east, data->ea_texture))
		exit_tex_error(data, "Invalid texture file");
	if (is_texture_path(data->floor_texture) && !load_texture(data,
			&data->tex_floor, data->floor_texture))
		exit_tex_error(data, "Invalid floor texture");
	else if (!is_texture_path(data->floor_texture))
		data->tex_floor.img_ptr = NULL;
	if (is_texture_path(data->sky_texture) && !load_texture(data,
			&data->tex_sky, data->sky_texture))
		exit_tex_error(data, "Invalid sky texture");
	else if (!is_texture_path(data->sky_texture))
		data->tex_sky.img_ptr = NULL;
	return (1);
}

static int	init_window(t_data *data)
{
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, data->screen.width,
			data->screen.height, "cub3D");
	if (!data->mlx.win_ptr)
		return (mess_error(1, "Window creation failed"), 0);
	data->mlx.img_ptr = mlx_new_image(data->mlx.mlx_ptr, data->screen.width,
			data->screen.height);
	if (!data->mlx.img_ptr)
		return (mess_error(1, "Image creation failed"), 0);
	data->mlx.img_data = mlx_get_data_addr(data->mlx.img_ptr, &data->mlx.bpp,
			&data->mlx.size_line, &data->mlx.endian);
	if (!data->mlx.img_data)
		return (mess_error(1, "Image data retrieval failed"), 0);
	return (1);
}

void	init_mlx(t_data *data)
{
	data->mlx.mlx_ptr = mlx_init();
	if (!data->mlx.mlx_ptr)
		mess_error(1, "MLX init failed");
	get_screen_size(data);
	if (!load_all_textures(data))
	{
		cleanup(data);
		exit(EXIT_FAILURE);
	}
	if (!init_window(data))
	{
		cleanup(data);
		exit(EXIT_FAILURE);
	}
	mlx_loop_hook(data->mlx.mlx_ptr, update, data);
}
