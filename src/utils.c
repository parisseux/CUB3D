#include "../inc/cub3d.h"

int mess_error(int exit_code, char *message)
{
    ft_putstr_fd("Error", 2);
    if (message)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(message, 2);
    }
    ft_putstr_fd("\n", 2);
    return (exit_code);
}