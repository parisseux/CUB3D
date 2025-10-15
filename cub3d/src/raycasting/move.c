/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:18:15 by grohr             #+#    #+#             */
/*   Updated: 2025/10/07 17:18:15 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// direction : vecteur (dir_x, dir_y) qui pointe vers où on regarde
// W/S : avance ou recule selon dir_x / dir_y
// A/D : latéral, perpendiculaire à la direction
//
// Exemple : si dir = (1,0), W avance en x+, S recule en x-, A/D agissent sur y.
// Déplacement est bloqué si on va vers un mur ('1' dans la map).
// Avant le move :
//
//         y-
//          ↑
//          |
//          |
// x- <-----@-----> x+   ← Le joueur regarde à droite (dir = (1, 0))
//          |
//          |
//          ↓
//         y+
//
// Déplacements :
//   W : avance → x+ (vers la droite)
//   S : recule → x- (vers la gauche)
//   A : strafe gauche → y- (vers le haut de l'écran)
//   D : strafe droite → y+ (vers le bas de l'écran)
//----------------------------------------------------
// DIAGONALE :
//         y-
//          ↑
//          |
//      A   |
//        ↖ @   → dir = (0.7, -0.7)
//          |
//          ↓
//         y+
//
// Déplacements :
//   W → avance en diagonale ↗
//   S → recule en diagonale ↙
//   A → strafe à gauche (perpendiculaire ↖ à dir)
//   D → strafe à droite (perpendiculaire ↘ à dir)
//
// Touche	|Vecteur appliqué
// 
// W		pos += dir * speed			→ avance vers où on regarde
// S		pos -= dir * speed			→ recule
// A		pos += perpend(dir) * speed	→ strafe gauche
// D		pos -= perpend(dir) * speed	→ strafe droite
//
// Et la perpendiculaire de (x, y) est (-y, x)

static bool	can_move(t_data *data, double x, double y)
{
	double	radius;

	radius = 0.2;
	if (data->map[(int)(y)][(int)(x - radius)] == '1')
		return (false);
	if (data->map[(int)(y)][(int)(x + radius)] == '1')
		return (false);
	if (data->map[(int)(y - radius)][(int)(x)] == '1')
		return (false);
	if (data->map[(int)(y + radius)][(int)(x)] == '1')
		return (false);
	return (true);
}

static void	move_forward_backward(t_data *data, int forward)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = data->move_speed;
	if (!forward)
		move_speed = -move_speed;
	new_x = data->player.pos_x + data->player.dir_x * move_speed;
	new_y = data->player.pos_y + data->player.dir_y * move_speed;
	if (can_move(data, new_x, data->player.pos_y))
		data->player.pos_x = new_x;
	if (can_move(data, data->player.pos_x, new_y))
		data->player.pos_y = new_y;
}

static void	strafe_left_right(t_data *data, int left)
{
	double	new_x;
	double	new_y;
	double	side_speed;

	side_speed = data->move_speed * 0.6;
	if (!left)
		side_speed = -side_speed;
	new_x = data->player.pos_x + data->player.dir_y * side_speed;
	new_y = data->player.pos_y - data->player.dir_x * side_speed;
	if (can_move(data, new_x, data->player.pos_y))
		data->player.pos_x = new_x;
	if (can_move(data, data->player.pos_x, new_y))
		data->player.pos_y = new_y;
}

void	move_player(t_data *data)
{
	if (data->keys.w)
		move_forward_backward(data, 1);
	if (data->keys.s)
		move_forward_backward(data, 0);
	if (data->keys.a)
		strafe_left_right(data, 1);
	if (data->keys.d)
		strafe_left_right(data, 0);
}
