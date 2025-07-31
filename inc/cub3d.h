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

//img_ptr : Pointeur vers l’image créée avec mlx_new_image()
//img_data : Adresse brute du buffer de pixels modifiable de l’image
//bpp : Bits par pixel (généralement 32 pour 4 octets : R, G, B, A)
//size_line : Nombre d’octets utilisés pour une ligne de pixels
//endian : Indique si les octets sont en big endian (1) ou little endian (0)

typedef struct s_mlx {
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    char *img_data;
    int bpp;
    int size_line;
    int endian;
} t_mlx;

typedef struct s_data {
    char **map;
    int fd_map;
    int height_map;
    t_mlx mlx;
} t_data;

//utils
int mess_error(int exit_code, char *message);

//parsing
char	**ft_get_map(char *file_path, t_data *game);
int		ft_check_map(t_data *game, char *file_name);
int     is_space(char c);

//init_mlx.c
void init_mlx(t_data *game);

//quit_clean.c
int key_hook(int keycode, t_data *game);
int close_window(t_data *game);
void cleanup(t_data *game);

#endif