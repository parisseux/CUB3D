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
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#ifdef __APPLE__
# include "../minilibx_macos/mlx.h"
#else
# include "../minilibx_linux/mlx.h"
#endif

typedef struct s_mlx {
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
} t_mlx;

typedef struct s_player {
	double	pos_x;
	double	pos_y;
	char	orientation;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
} t_player;

typedef struct s_keys {
	int		w;
	int		s;
	int		a;
	int		d;
	int		left;
	int		right;
} t_keys;

typedef struct s_ray {
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
} t_ray;

typedef struct s_data {
	char		**map;
	int			fd_map;
	int			height_map;
	t_mlx		mlx;
	t_player	player;
	t_keys		keys;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color;
	int			ceiling_color;
} t_data;

// utils.c
int		mess_error(int exit_code, char *message);
void	ft_free_split(char **split);

// parsing/check_map.c
int		ft_check_map(t_data *game, char *file_name);

// parsing/get_map.c
char	**ft_get_map(char *file_path, t_data *game);

// parsing/parsing_utils.c
int		is_space(char c);

// parsing/parse_elements.c
int		parse_elements(t_data *game, char *file_path);

// player/player.c
int		init_player(t_data *game);

// mlx/init_mlx.c
void	init_mlx(t_data *data);

// mlx/quit_clean.c
int		close_window(t_data *data);
void	cleanup(t_data *data);

// raycasting/raycasting.c
void	init_camera(t_data *data);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);

// raycasting/move.c
void	move_player(t_data *data);
void	rotate_player(t_data *data);

// raycasting/render.c
void	draw_column(t_data *data, int x, int start, int end);
int		render_frame(t_data *data);

// raycasting/pixel.c
void	draw_pixel(t_mlx *mlx, int x, int y, int color);

#endif