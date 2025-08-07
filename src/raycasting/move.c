#include "../../inc/cub3d.h"
#include <math.h>

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
void move_player(t_data *data)
{
	double	move_speed = CALC_MOVE_SPEED(data);
	double	side_speed = move_speed * 0.6;
	double	new_x;
	double	new_y;

	if (data->keys.w)
	{
		new_x = data->player.pos_x + data->player.dir_x * move_speed;
		new_y = data->player.pos_y + data->player.dir_y * move_speed;
		if (data->map[(int)data->player.pos_y][(int)new_x] != '1')
			data->player.pos_x = new_x;
		if (data->map[(int)new_y][(int)data->player.pos_x] != '1')
			data->player.pos_y = new_y;
		data->sky_offset += move_speed * 0.1; // Augmente l'offset pour que les nuages reculent
	}
	if (data->keys.s)
	{
		new_x = data->player.pos_x - data->player.dir_x * move_speed;
		new_y = data->player.pos_y - data->player.dir_y * move_speed;
		if (data->map[(int)data->player.pos_y][(int)new_x] != '1')
			data->player.pos_x = new_x;
		if (data->map[(int)new_y][(int)data->player.pos_x] != '1')
			data->player.pos_y = new_y;
		data->sky_offset -= move_speed * 0.1; // Diminue l'offset pour que les nuages avancent
	}
	if (data->keys.a)
	{
		new_x = data->player.pos_x + data->player.dir_y * side_speed;
		new_y = data->player.pos_y - data->player.dir_x * side_speed;
		if (data->map[(int)data->player.pos_y][(int)new_x] != '1')
			data->player.pos_x = new_x;
		if (data->map[(int)new_y][(int)data->player.pos_x] != '1')
			data->player.pos_y = new_y;
	}
	if (data->keys.d)
	{
		new_x = data->player.pos_x - data->player.dir_y * side_speed;
		new_y = data->player.pos_y + data->player.dir_x * side_speed;
		if (data->map[(int)data->player.pos_y][(int)new_x] != '1')
			data->player.pos_x = new_x;
		if (data->map[(int)new_y][(int)data->player.pos_x] != '1')
			data->player.pos_y = new_y;
	}
	
	if (data->sky_offset < 0.0)
		data->sky_offset += 1.0;
	else if (data->sky_offset >= 1.0)
		data->sky_offset -= 1.0;
}

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

#define ROTATE_VEC(x, y, angle, out_x, out_y)                                  \
	(out_x) = (x) * cos(angle) - (y) * sin(angle);                             \
	(out_y) = (x) * sin(angle) + (y) * cos(angle)

void rotate_player(t_data *data)
{
	double rot_speed = CALC_ROT_SPEED(data);
	if (data->keys.left)
	{
		ROTATE_VEC(data->player.dir_x, data->player.dir_y, -rot_speed,
				   data->player.dir_x, data->player.dir_y);
		ROTATE_VEC(data->player.plane_x, data->player.plane_y, -rot_speed,
				   data->player.plane_x, data->player.plane_y);
	}
	if (data->keys.right)
	{
		ROTATE_VEC(data->player.dir_x, data->player.dir_y, rot_speed,
				   data->player.dir_x, data->player.dir_y);
		ROTATE_VEC(data->player.plane_x, data->player.plane_y, rot_speed,
				   data->player.plane_x, data->player.plane_y);
	}
}
