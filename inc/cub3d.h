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
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    char *img_data;
    int bpp;
    int size_line;
    int endian;
} t_mlx;

typedef struct s_player {
    double pos_x;
    double pos_y;
    char orientation; // 'N', 'S', 'E', 'W'
    double dir_x;     // Direction du joueur (x)
    double dir_y;     // Direction du joueur (y)
    double plane_x;   // Plan de la caméra (x)
    double plane_y;   // Plan de la caméra (y)
} t_player;

typedef struct s_keys {
    int w;            // Avancer
    int s;            // Reculer
    int a;            // Strafe gauche
    int d;            // Strafe droite
    int left;         // Tourner à gauche
    int right;        // Tourner à droite
} t_keys;

typedef struct s_data {
    char **map;
    int fd_map;
    int height_map;
    t_mlx mlx;
    t_player player;
    t_keys keys;      // État touches
    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;
    int floor_color;
    int ceiling_color;
} t_data;

//utils
int     mess_error(int exit_code, char *message);
void    ft_free_split(char **split);

//parsing
char	**ft_get_map(char *file_path, t_data *game);
int		ft_check_map(t_data *game, char *file_name);
int     is_space(char c);
int		parse_elements(t_data *game, char *file_path);
int		init_player(t_data *game);

//init_mlx.c
void    init_mlx(t_data *game);

//quit_clean.c
int     close_window(t_data *game);
void    cleanup(t_data *game);

//raycasting.c
void    init_camera(t_data *game);
int     render_frame(t_data *game);
int     key_press(int keycode, t_data *game);
int     key_release(int keycode, t_data *game);

#endif