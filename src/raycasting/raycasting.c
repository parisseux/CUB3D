#include "../../inc/cub3d.h"


// Initialise la direction du joueur + le plan de la caméra selon l'orientation
// Le plan caméra :
//		-> est perpendiculaire à la direction 
//		-> et détermine le champ de vision.
// Le vecteur direction (dir_x, dir_y) indique où regarde le joueur :
//   - 'N' (nord) : dir = (0, -1), plane = (0.66, 0)
//   - 'S' (sud)  : dir = (0,  1), plane = (-0.66, 0)
//   - 'E' (est)  : dir = (1,  0), plane = (0, 0.66)
//   - 'W' (ouest): dir = (-1, 0), plane = (0, -0.66)
//
// Le plan caméra est utilisé dans le raycasting pour générer le rendu 3D
// La valeur 0.66 permet un FOV (Field of View) d'environ 66° (valeur courante)
// Exemple en 2D (vue du dessus) :
//
//         y
//         ↑
//         |       dir = (0, -1)
//         |       (le joueur regarde vers le haut)
//         |
//         |       champ de vision
//         |    ↖------------O------------↗
//         |     plane_x = ±0.66 (perp. à la dir_y)
//         |
//         +------------------------------→ x
//
// "O" = position du joueur
//
// Exemple : si on regarde vers le nord (0, -1),
// le plan est horizontal (sur x) : (-0.66, 0) et (0.66, 0)
//
// Réinitialise aussi toutes les touches (WASD, flèches) à 0 (non pressées).

void init_keys(t_data *data)
{
	data->keys.w = 0;
	data->keys.s = 0;
	data->keys.a = 0;
	data->keys.d = 0;
	data->keys.left = 0;
	data->keys.right = 0;
}

void init_dir(t_player *p, double x, double y)
{
	p->dir_x = x;
	p->dir_y = y;
}

void init_plane(t_player *p, double x, double y)
{
	p->plane_x = x;
	p->plane_y = y;
}

void	init_camera(t_data *data)
{
	t_player	*p;

	p = &data->player;
	if (p->orientation == 'N')
	{
		init_dir(p, 0, -1);
		init_plane(p, 0.66, 0);
	}
	else if (p->orientation == 'S')
	{
		init_dir(p, 0, 1);
		init_plane(p, -0.66, 0);
	}
	else if (p->orientation == 'E')
	{
		init_dir(p, 1, 0);
		init_plane(p, 0, 0.66);
	}
	else if (p->orientation == 'W')
	{
		init_dir(p, -1, 0);
		init_plane(p, 0, -0.66);
	}
	init_keys(data);
}

int key_press(int keycode, t_data *data)
{
	if (keycode == 53 || keycode == 65307)
	{
		cleanup(data);
		exit(0);
	}
	if (keycode == 13 || keycode == 119)
		data->keys.w = 1;
	if (keycode == 1 || keycode == 115)
		data->keys.s = 1;
	if (keycode == 0 || keycode == 97)
		data->keys.a = 1;
	if (keycode == 2 || keycode == 100)
		data->keys.d = 1;
	if (keycode == 123 || keycode == 65361)
		data->keys.left = 1;
	if (keycode == 124 || keycode == 65363)
		data->keys.right = 1;
	if (keycode == 24 || keycode == 61)
		data->sky_scale += 1;
	if ((keycode == 27 || keycode == 45) && data->sky_scale > 1)
		data->sky_scale -= 1;
	return (0);
}

int key_release(int keycode, t_data *data)
{
	if (keycode == 13 || keycode == 119)
		data->keys.w = 0;
	if (keycode == 1 || keycode == 115)
		data->keys.s = 0;
	if (keycode == 0 || keycode == 97)
		data->keys.a = 0;
	if (keycode == 2 || keycode == 100)
		data->keys.d = 0;
	if (keycode == 123 || keycode == 65361)
		data->keys.left = 0;
	if (keycode == 124 || keycode == 65363)
		data->keys.right = 0;
	return (0);
}
