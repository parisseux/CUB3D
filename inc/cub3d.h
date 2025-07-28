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


typedef struct s_data {
    char **map;
    int fd_map;
    int height_map;
} t_data;


//utils
int mess_error(int exit_code, char *message);

//parsing
char	**ft_get_map(char *file_path, t_data *game);
int		ft_check_map(t_data *game, char *file_name);
int     is_space(char c);

#endif 
