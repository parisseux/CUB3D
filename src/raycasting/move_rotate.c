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

static bool can_move(t_data *data, double x, double y)
{
	double radius;

	radius = 0.2; //marge de securit; avec le mur
    if (data->map[(int)(y)][(int)(x - radius)] == '1')
        return false;
    if (data->map[(int)(y)][(int)(x + radius)] == '1')
        return false;
    if (data->map[(int)(y - radius)][(int)(x)] == '1')
        return false;
    if (data->map[(int)(y + radius)][(int)(x)] == '1')
        return false;
    return true;
}

static void move_forward_backward(t_data *data, int forward)
{
	double new_x;
	double new_y;
	double move_speed;

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

static void strafe_left_right(t_data *data, int left)
{
	double new_x;
	double new_y;
	double side_speed;

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

void move_player(t_data *data)
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

void	rotate_player(t_data *data)
{
	double	rot_speed;
	t_vec	new_dir;
	t_vec	new_plane;

	rot_speed = data->rot_speed;
	if (data->keys.left)
	{
		new_dir = rotate_vec(data->player.dir_x, data->player.dir_y, -rot_speed);
		new_plane = rotate_vec(data->player.plane_x, data->player.plane_y, -rot_speed);
		data->player.dir_x = new_dir.x;
		data->player.dir_y = new_dir.y;
		data->player.plane_x = new_plane.x;
		data->player.plane_y = new_plane.y;
	}
	if (data->keys.right)
	{
		new_dir = rotate_vec(data->player.dir_x, data->player.dir_y, rot_speed);
		new_plane = rotate_vec(data->player.plane_x, data->player.plane_y, rot_speed);
		data->player.dir_x = new_dir.x;
		data->player.dir_y = new_dir.y;
		data->player.plane_x = new_plane.x;
		data->player.plane_y = new_plane.y;
	}
}
