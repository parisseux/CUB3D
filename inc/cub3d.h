#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"


typedef struct s_data {
    char **map;
    int fd_map;
} t_data;


//parsing
char	**ft_get_map(char *file_path, t_data *game);
int		ft_check_map(t_data *game, char *file_name);
int		ft_check_format_cub(char *file_name);
int		ft_check_tiles(t_data *game);

#endif 
