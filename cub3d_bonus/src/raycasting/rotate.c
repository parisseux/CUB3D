/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:22:56 by grohr             #+#    #+#             */
/*   Updated: 2025/10/07 17:22:57 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Tourner le joueur
// Fait tourner :
//  - son vecteur direction (dir_x, dir_y)
//  - le plan caméra (plane_x, plane_y) : définit le champ de vision.
//
// On fait une rotation 2D autour de l'origine (formule wiki).
// On a θ = rot_speed (vitesse de rotation ecran):
//
// x' = x * cos(θ) - y * sin(θ)
// y' = x * sin(θ) + y * cos(θ)
//
// Si angle négatif -> tourne à gauche
// Si angle positif -> tourne à droite.
//
// Le plan caméra (plane_x, plane_y) tourne avec la dir -> garder l'effet 3D.

static void	init_rotate_value(t_data *data, t_vec new_dir, t_vec new_plane)
{
	data->player.dir_x = new_dir.x;
	data->player.dir_y = new_dir.y;
	data->player.plane_x = new_plane.x;
	data->player.plane_y = new_plane.y;
}

void	rotate_player(t_data *data)
{
	double	rot_speed;
	t_vec	new_dir;
	t_vec	new_plane;

	rot_speed = data->rot_speed;
	if (data->keys.left)
	{
		new_dir = rotate_vec(data->player.dir_x,
				data->player.dir_y, -rot_speed);
		new_plane = rotate_vec(data->player.plane_x,
				data->player.plane_y, -rot_speed);
		init_rotate_value(data, new_dir, new_plane);
	}
	if (data->keys.right)
	{
		new_dir = rotate_vec(data->player.dir_x, data->player.dir_y, rot_speed);
		new_plane = rotate_vec(data->player.plane_x,
				data->player.plane_y, rot_speed);
		init_rotate_value(data, new_dir, new_plane);
	}
}
