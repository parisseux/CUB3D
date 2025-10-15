/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:18:50 by grohr             #+#    #+#             */
/*   Updated: 2025/10/08 15:52:40 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	close_window(t_data *data)
{
	cleanup(data);
	exit(0);
	return (0);
}

void	destroy_texture(t_data *data)
{
	if (data->tex_north.img_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->tex_north.img_ptr);
	if (data->tex_south.img_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->tex_south.img_ptr);
	if (data->tex_west.img_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->tex_west.img_ptr);
	if (data->tex_east.img_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->tex_east.img_ptr);
	if (data->tex_floor.img_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->tex_floor.img_ptr);
	if (data->tex_sky.img_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->tex_sky.img_ptr);
}

static void	cleanup_mlx(t_data *data)
{
	if (!data->mlx.mlx_ptr)
		return ;
	if (data->mlx.img_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img_ptr);
	if (data->mlx.win_ptr)
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	mlx_destroy_display(data->mlx.mlx_ptr);
	free(data->mlx.mlx_ptr);
	data->mlx.mlx_ptr = NULL;
}

static void	cleanup_textures(t_data *data)
{
	if (data->no_texture)
		free(data->no_texture);
	if (data->so_texture)
		free(data->so_texture);
	if (data->we_texture)
		free(data->we_texture);
	if (data->ea_texture)
		free(data->ea_texture);
	if (data->sky_texture)
		free(data->sky_texture);
	if (data->floor_texture)
		free(data->floor_texture);
}

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	destroy_texture(data);
	cleanup_mlx(data);
	cleanup_textures(data);
	if (data->map)
		ft_free_split(data->map);
	free(data);
}
