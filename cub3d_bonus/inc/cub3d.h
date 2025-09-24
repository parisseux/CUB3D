#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include "../../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>

# ifdef __APPLE__
#  include "../../minilibx_macos/mlx.h"
# else
#  include "../../minilibx-linux/mlx.h"
# endif

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define BASE_MOVE_SPEED  0.055
# define BASE_ROT_SPEED   0.03
# define REFERENCE_WIDTH  1280.0
# define DEFAULT_WIDTH    1280
# define DEFAULT_HEIGHT   720
# define MOVE_SPEED       0.08
# define ROT_SPEED        0.025
# define FPS			  30
# define FRAME_TIME 	  33.33
# define MINIMAP_MARGIN     10
# define MINIMAP_SCALE 		10
# define PLAYER_SIZE 4  

typedef struct s_sprite
{
    void    *img_ptr;
    int     *pixels;
    int     width;
    int     height;
} t_sprite;

typedef struct s_sky
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	angle;
	double	scale;
	double	offset;
}	t_sky;

typedef struct s_floor
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	denom;
	double	row_distance;
	double	cam;
	double	floor_x;
	double	floor_y;
}	t_floor;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_resolution_profil
{
	char	*name;
	int		width;
	int		height;
	char	*description;
}	t_resolution_profile;

typedef struct s_screen
{
	int	width;
	int	height;
}	t_screen;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_mlx;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	char	orientation;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_keys
{
	int		w;
	int		s;
	int		a;
	int		d;
	int		left;
	int		right;
	int		run;
}	t_keys;

typedef struct s_texture
{
	void	*img_ptr;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_column
{
	double		pdist;
	int			line_h;
	int			draw_start;
	int			draw_end;
	int			y0c;
	int			y1c;
	int			tex_x;
	t_texture	*tex;

}	t_column;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_dist;
}	t_ray;

typedef struct s_data
{
	char		**map;
	int			fd_map;
	int			height_map;
	t_mlx		mlx;
	t_player	player;
	t_keys		keys;
	t_ray		ray;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		*floor_texture;
	char		*sky_texture;
	double		sky_scale;
	double		sky_offset;
	t_texture	tex_north;
	t_texture	tex_south;
	t_texture	tex_west;
	t_texture	tex_east;
	t_texture	tex_floor;
	t_texture	tex_sky;
	t_screen	screen;
	double		move_speed;
	double		rot_speed;
	int			prev_mouse_x;
	double		mouse_sensitivity;
	t_sprite arms;
    int      arm_frame;
}	t_data;

//minimap.c
void		draw_minimap(t_data *data);

// utils.c
int			mess_error(int exit_code, char *message);
void		ft_free_split(char **split);

// parsing/check_map.c
int			ft_check_map(t_data *game, char *file_name);
int			ft_check_border_map(char **map, int i, int j);

// parsing/get_map.c
char		**ft_get_map(char *file_path, t_data *game);

// parsing/parsing_utils.c
int			is_space(char c);
bool		only_space(char *line);
int			is_valid_rgb(int r, int g, int b);
char		*skip_empty_lines(int fd);

// parsing/parse_elements.c
int			parse_elements(t_data *game, int fd);

// player/player.c
int			init_player(t_data *game);

// mlx/init_mlx.c
void		init_mlx(t_data *data);
void		get_screen_size(t_data *data);

// mlx/quit_clean.c
int			close_window(t_data *data);
void		cleanup(t_data *data);

// raycasting/raycasting.c
void		init_camera(t_data *data);
int			key_press(int keycode, t_data *data);
int			key_release(int keycode, t_data *data);

//mouse.c
int			mouse_move(int x, int y, t_data *data);
int			mouse_release(int button, int x, int y, void *param);
int			mouse_press(int button, int x, int y, void *param);

//raycastin/keys
void		init_keys(t_data *data);

// raycasting/move.c
void		move_player(t_data *data);
void		rotate_player(t_data *data);

// raycasting/render.c
int			render_frame(t_data *data);

// raycasting/pixel.c
void		draw_pixel(int x, int y, int color, t_data *data);
int			color_tex(t_texture *tex, int tx, int ty);

// raycasting/update.c
int			update(t_data *data);

//raycasting1.c
void		ray_dir(t_data *data, int x, double *rx, double *ry);
void		init_dda(t_data *data, double rx, double ry, t_ray *ray);
void		dda_walk(t_data *data, t_ray *ray);

//raycasting2.c
double		dist_perp_wall(t_data *data, t_ray *ray, double rx, double ry);
t_texture	*wall_tex(t_data *data, t_ray *ray, double rx, double ry);
void		draw_floor(t_data *data, int x, int y);
void		draw_wall(t_data *data, int x, t_column *col);
void		draw_sky(t_data *data, int x, int y);
int			get_tex_color(t_texture *tex, int tex_x, int tex_y);

//maths_utils 
double		calc_move_speed(t_data *data);
double		calc_rot_speed(t_data *data);
int			pixel_skip(t_data *data);
t_vec		rotate_vec(double x, double y, double angle);
double		dabs(double x);

//time.c 
long		get_time_ms(void);

//arms.c
void draw_arm(t_data *data);

#endif