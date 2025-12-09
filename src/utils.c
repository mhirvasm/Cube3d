
#include "cub3d.h"

int	check_extension(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (!(arg[len - 1] == 'b' && arg[len - 2] == 'u' && arg[len - 3] == 'c'
		&& arg[len - 4] == '.'))
		return (1);
	return (0);
}

int	gettextures(t_map *map, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		if (line[0] == 'N')
			map->northtexture = ft_strdup(line);
		else if (line[0] == 'S')
			map->southtexture = ft_strdup(line);
		else if (line[0] == 'E')
			map->easttexture = ft_strdup(line);
		else if (line[0] == 'W')
			map->westtexture = ft_strdup(line);
		else if (line[0] == 'F')
			map->floor = ft_strdup(line);
		else if (line[0] == 'C')
		{
			map->ceiling = ft_strdup(line);
			free(line);
			break ;
		}
		if (!(map->northtexture && map->southtexture && map->easttexture
			&& map->westtexture && map->floor && map->ceiling))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	close (fd);
	return (0);
}
