#include "../../inc/cub3d.h"

// Dit quelle texture afficher (N/S/E/O) en fonction de la dir
// du rayon et du côté du mur touché (horizontal ou vertical)
// Si le mur est vertical (side = 0), on regarde ray_x
// Si horizontal (side = 1), on regarde ray_y
// Exemple : ray->side == 0 && ray_x > 0 => mur Est
static void	get_wall_dir(t_ray *ray, double ray_x, double ray_y, t_data *data, t_texture **tex)
{
	if (ray->side == 0)
	{
		if (ray_x > 0)
			*tex = &data->tex_east;
		else
			*tex = &data->tex_west;
	}
	else
	{
		if (ray_y > 0)
			*tex = &data->tex_south;
		else
			*tex = &data->tex_north;
	}
}

// Récupère la couleur d'un pixel dans une texture à la position (tex_x, tex_y).
// On calcule l'adresse mémoire du pixel (data + offset).
// Si endian = 0 (little endian), on lit R,G,B à la main.
// Sinon, on lit 4 octets directement (big endian).
// Défaut : si color=0 → rouge ; hors limites → gris.
static int	get_tex_color(t_texture *tex, int tex_x, int tex_y)
{
	char	*dst;
	int		color;

	if (!tex->data)
		return (0xFF0000);
	if (tex_x >= 0 && tex_x < tex->width && tex_y >= 0 && tex_y < tex->height)
	{
		dst = tex->data + (tex_y * tex->size_line + tex_x * (tex->bpp / 8));
		if (tex->endian == 0)
		{
			unsigned char *pixel = (unsigned char *)dst;
			color = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
		}
		else
			color = *(unsigned int *)dst;
		if (color == 0)
			color = 0xFF0000;
	}
	else
		color = 0x808080;
	return (color);
}

// Initialise le rayon en fonction de la colonne x de l'écran.
// camera_x ∈ [-1, 1] (gauche à droite).
// Combine la direction du joueur + son plan caméra :
// ray = dir + plane * camera_x (cf. Wiki Raycasting)
static void	init_ray(t_data *data, int x, double *ray_x, double *ray_y)
{
	double	camera_x;

	camera_x = 2 * x / (double)data->screen.width - 1;
	*ray_x = data->player.dir_x + data->player.plane_x * camera_x;
	*ray_y = data->player.dir_y + data->player.plane_y * camera_x;
}

// init_ray : Récupérer la direction du rayon pour la colonne x
//
// Calculer la position exacte de l'impact sur le mur
// if (data->ray.side == 0) :   -> Mur vertical
// else                         -> Mur horizontal
// wall_x -= (int)wall_x;       -> Prendre la partie fractionnaire
void	draw_column(t_data *data, int x, int start, int end, t_texture *tex)
{
	int		y;
	int		tex_x;
	int		tex_y;
	double	wall_x;
	double	ray_x, ray_y;

	init_ray(data, x, &ray_x, &ray_y);
	if (data->ray.side == 0)
		wall_x = data->player.pos_y + data->ray.perp_dist * ray_y;
	else
		wall_x = data->player.pos_x + data->ray.perp_dist * ray_x;
	wall_x -= (int)wall_x;
	tex_x = (int)(wall_x * (double)tex->width);
	if ((data->ray.side == 0 && ray_x < 0) || (data->ray.side == 1 && ray_y > 0))
		tex_x = tex->width - tex_x - 1;
	y = 0;
	while (y < data->screen.height)
	{
		if (y < start)
			draw_pixel(&data->mlx, x, y, data->ceiling_color, data);
		else if (y >= start && y <= end)
		{
			tex_y = (int)((y - start) * tex->height / (end - start + 1));
			draw_pixel(&data->mlx, x, y, get_tex_color(tex, tex_x, tex_y), data);
		}
		else
			draw_pixel(&data->mlx, x, y, data->floor_color, data);
		y++;
	}
}

// Initialise les distances du rayon à chaque grille (delta_dist)
// ainsi que les directions de pas (step_x/y).
// side_dist = distance initiale à la première ligne/colonne de mur.
// Exemple : si ray_x < 0, on va vers la gauche donc step_x = -1.
static void	setup_ray(t_data *data, double ray_x, double ray_y, t_ray *ray)
{
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
	ray->delta_dist_x = fabs(1 / ray_x);
	ray->delta_dist_y = fabs(1 / ray_y);
	if (ray_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.pos_x) * ray->delta_dist_x;
	}
	if (ray_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.pos_y) * ray->delta_dist_y;
	}
}

// Envoie le rayon dans la map jusqu'à ce qu'il touche un mur ('1') ou dépasse.
// À chaque étape, on choisit la plus courte distance à un côté de bloc :
// - Si side_dist_x < side_dist_y, on avance en x
// - Sinon, en y
// On met ray->side = 0 (vertical) ou 1 (horizontal)
// On s'arrête si on sort des limites de la map ou qu'on touche un mur.
static void	cast_ray(t_data *data, t_ray *ray)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_x < 0
			|| ray->map_y >= data->height_map
			|| ray->map_x >= (int)ft_strlen(data->map[ray->map_y]))
		{
			ray->hit = 1;
			return;
		}
		if (data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

// Calcule la hauteur du mur à dessiner (proportionnelle à distance)
// On utilise la distance perpendiculaire (perp_dist) pour éviter la distorsion
// start/end = plage de lignes (pixels y) où le mur doit être dessiné
static void	calc_wall(t_data *data, t_ray *ray, int *start, int *end)
{
	int	height;

	if (ray->side == 0)
		ray->perp_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_dist = (ray->side_dist_y - ray->delta_dist_y);
	height = (int)(data->screen.height / ray->perp_dist);
	*start = -height / 2 + data->screen.height / 2;
	if (*start < 0)
		*start = 0;
	*end = height / 2 + data->screen.height / 2;
	if (*end >= data->screen.height)
		*end = data->screen.height - 1;
}

// Boucle de rendu : pour chaque colonne de l'écran (x)
// - Initialise un rayon (init_ray)
// - Calcule sa trajectoire (setup_ray)
// - Trouve le point d'impact (cast_ray)
// - Calcule la hauteur du mur à afficher (calc_wall)
// - Détermine la bonne texture (get_wall_dir)
// - Dessine la colonne (draw_column)
// Puis affiche l'image dans la fenêtre.
int	render_frame(t_data *data)
{
	int			x;
	double		ray_x;
	double		ray_y;
	t_texture	*tex;
	int			start;
	int			end;

	x = 0;
	while (x < data->screen.width)
	{
		init_ray(data, x, &ray_x, &ray_y);
		setup_ray(data, ray_x, ray_y, &data->ray);
		cast_ray(data, &data->ray);
		calc_wall(data, &data->ray, &start, &end);
		get_wall_dir(&data->ray, ray_x, ray_y, data, &tex);
		draw_column(data, x, start, end, tex);
		x++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->mlx.img_ptr, 0, 0);
	return (0);
}
