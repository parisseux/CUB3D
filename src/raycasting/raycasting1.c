#include "../../inc/cub3d.h"

//helper vectors
double  dabs(double x)
{
	return x < 0 ? -x : x;
}

//calcule la direction du rayon dans le monde pour la colone x. On part de la direction
// du joueur et on l'élargit avec le plan camera
//formule: camera_x = 2*x / width -1 et ray = dir + plane * camera_x
void ray_dir(t_data *data, int x, double *rx, double *ry)
{
	double camera_x;
	
	camera_x = (2.0 * x) / (double)data->screen.width - 1.0;
	*rx = data->player.dir_x + data->player.plane_x * camera_x;
	*ry = data->player.dir_y + data->player.plane_y * camera_x;
}

//prepare les variables necessaires au DDA (digital differential Analyzer)
// place le rayon dans la bonne case de départ (mpa_x et map_y)
// calcule les distances fixes nécessaire pour chahir chaque case (delta)
// determine la direction du pas (+X, -X, +Y, -Y)
//calcule la distance inititlae à la première frontiere (side_dist)
void init_dda(t_data *data, double rx, double ry, t_ray *ray)
{

	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
	ray->delta_dist_x = dabs(1.0/rx);
	ray->delta_dist_y = dabs(1.0/ry);
	if (rx < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.pos_x) * ray->delta_dist_x;
	}
	if (ry < 0)
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


static void update_case_visited(t_ray *ray)
{
    if (ray->side_dist_x < ray->side_dist_y)
		{ 
			ray->side_dist_x += ray->delta_dist_x; 
			ray->map_x += ray->step_x; 
			ray->side = 0; 
		}
		else if (ray->side_dist_y < ray->side_dist_x)
		{ 
			ray->side_dist_y += ray->delta_dist_y; 
			ray->map_y += ray->step_y; 
			ray->side = 1; 
		}
		else 
		{
   			 ray->side_dist_x += ray->delta_dist_x;
    		ray->map_x += ray->step_x;
    		ray->side = 0;
		}
}

//avance le rayon "case par Case" dans lam ap jusqu'à qu'il touche un mur
//ou qu'il sorte des limites
//a chaque étape, on franchit la prochaine frontière verticale/horizontale 
//la plus proche et on met a jour la case visité
void dda_walk(t_data *data, t_ray *ray)
{
	ray->hit = 0;

	while (!ray->hit)
	{
        update_case_visited(ray);
		if (ray->map_y < 0 || ray->map_x < 0 || ray->map_y >= data->height_map
			|| ray->map_x >= (int)ft_strlen(data->map[ray->map_y]))
		{ 
			ray->hit = 1; 
			return; 
		}
		if (data->map[ray->map_y][ray->map_x] == '1') 
			ray->hit = 1;
	}
}
