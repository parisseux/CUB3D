/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:17:32 by grohr             #+#    #+#             */
/*   Updated: 2025/10/07 17:28:07 by grohr            ###   ########.fr       */
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
}

void	cleanup(t_data *data)
{
	destroy_texture(data);
	if (data->mlx.img_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img_ptr);
	if (data->mlx.win_ptr)
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	if (data->mlx.mlx_ptr)
		mlx_destroy_display(data->mlx.mlx_ptr);
	if (data->mlx.mlx_ptr)
		free(data->mlx.mlx_ptr);
	if (data->no_texture)
		free(data->no_texture);
	if (data->so_texture)
		free(data->so_texture);
	if (data->we_texture)
		free(data->we_texture);
	if (data->ea_texture)
		free(data->ea_texture);
	if (data->map)
		ft_free_split(data->map);
	if (data)
		free(data);
}
