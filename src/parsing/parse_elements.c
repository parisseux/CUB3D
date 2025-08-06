#include "../../inc/cub3d.h"

// static int	is_valid_rgb(int r, int g, int b)
// {
// 	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
// }

// //*color = (r << 16) | (g << 8) | b --> Convertir en int (format RGB)
// static int	parse_color(char *line, int *color)
// {
// 	char	*trimmed;
// 	char	**rgb;
// 	int r, g, b;

//     trimmed = ft_strtrim(line + 2, " \t\n");
//     if (!trimmed)
//         return (0);
//     rgb = ft_split(trimmed, ',');
//     free(trimmed);
//     if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
//     {
//         ft_free_split(rgb);
//         return (0);
//     }
//     r = ft_atoi(rgb[0]);
//     g = ft_atoi(rgb[1]);
//     b = ft_atoi(rgb[2]);
//     if (!is_valid_rgb(r, g, b))
//     {
//         ft_free_split(rgb);
//         return (0);
//     }
//     *color = (r << 16) | (g << 8) | b;
//     //DEBUG
// 	//printf("Parsed color: R=%d, G=%d, B=%d, color=0x%X\n", r, g, b, *color);
//     ft_free_split(rgb);
//     return (1);
// }

static int	parse_texture(char *line, char **texture)
{
	char	*trimmed;

	if (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0)
		trimmed = ft_strtrim(line + 2, " \t\n");
	else
		trimmed = ft_strtrim(line + 3, " \t\n");
	if (!trimmed || !*trimmed)
	{
		free(trimmed);
		return (0);
	}
	*texture = trimmed;
	return (1);
}

static int is_element_line(char *line)
{
	if (!line || !*line || is_space(line[0]))
		return (0);
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 ||
			ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

int parse_elements(t_data *game, int fd)
{
	char *line;
	int elements_found = 0;

	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line && elements_found < 6)
	{
		if (is_element_line(line))
		{
			if (ft_strncmp(line, "NO ", 3) == 0 && !game->no_texture)
				elements_found += parse_texture(line, &game->no_texture);
			else if (ft_strncmp(line, "SO ", 3) == 0 && !game->so_texture)
				elements_found += parse_texture(line, &game->so_texture);
			else if (ft_strncmp(line, "WE ", 3) == 0 && !game->we_texture)
				elements_found += parse_texture(line, &game->we_texture);
			else if (ft_strncmp(line, "EA ", 3) == 0 && !game->ea_texture)
				elements_found += parse_texture(line, &game->ea_texture);
			else if (ft_strncmp(line, "F ", 2) == 0 && !game->floor_texture)
				elements_found += parse_texture(line, &game->floor_texture);
			else if (ft_strncmp(line, "C ", 2) == 0 && !game->sky_texture)
				elements_found += parse_texture(line, &game->sky_texture);
			// else if (ft_strncmp(line, "F ", 2) == 0 && game->floor_color == -1)
			// 	elements_found += parse_color(line, &game->floor_color);
			// else if (ft_strncmp(line, "C ", 2) == 0 && game->ceiling_color == -1)
			// 	elements_found += parse_color(line, &game->ceiling_color);
			else
			{
				free(line);
				return (mess_error(0, "Élément dup ou invalide"));
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (elements_found == 6);
}
