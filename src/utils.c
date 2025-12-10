
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

static int	texture_strdup(t_map *map, char *line)
{
	if (line[0] == 'N')
		map->textures[NORTH] = ft_strdup(line);
	else if (line[0] == 'S')
		map->textures[SOUTH] = ft_strdup(line);
	else if (line[0] == 'E')
		map->textures[EAST] = ft_strdup(line);
	else if (line[0] == 'W')
		map->textures[WEST] = ft_strdup(line);
	else if (line[0] == 'F')
		map->textures[FLOOR] = ft_strdup(line);
	else if (line[0] == 'C')
		map->textures[CEILING] = ft_strdup(line);
	else
	{
		free(line);
		return (1);
	}
	map->textures[6] = NULL;
	return (0);
}

static void	texture_truncate(char **textures)
{
	int		i;
	int		j;
	int		l;
	char	*line;

	i = -1;
	while (textures[++i])
	{
		j = 0;
		while (textures[i][j])
		{
			if (textures[i][j] == '/')
			{
				line = malloc((ft_strlen(textures[i]) - j) * sizeof(char));
				l = 0;
				while (textures[i][j])
					line[l++] = textures[i][j++];
				line[l] = '\0';
				free(textures[i]);
				textures[i] = ft_strdup(line);
				free(line);
				break ;
			}
			j++;
		}
	}
}

int	gettextures(t_map *map, int fd)
{
	char	*line;
	int		i;

	i = 0;
	map->textures = malloc(6 * sizeof(char *));
	while (1)
	{
		line = get_next_line(fd);
		if (line[0] == '\n')
			break ;
		if (texture_strdup(map, line))
			return (1);
		free(line);
	}
	if (!(map->textures[NORTH] && map->textures[SOUTH]
		&& map->textures[EAST] && map->textures[WEST]
		&& map->textures[FLOOR] && map->textures[CEILING]))
	{
		free(line);
		return (1);
	}
	texture_truncate(map->textures);
	return (0);
}
