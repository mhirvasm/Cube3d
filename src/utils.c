
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

int	line_check(char *line, char	c, char d)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\f'
			|| line[i] == '\v' || line[i] == '\r')
			i++;
	if (line[i] == '\n')
		return (0);
	if (line[i] == '1')
		return (1);
	if (line[i] == c && line[i + 1] == d)
		return (0);
	return (1);
}

static int	texture_strdup(t_map *map, char *line)
{
	if (!line_check(line, 'N', 'O'))
		map->textures[NORTH] = ft_strdup(line);
	else if (!line_check(line, 'S', 'O'))
		map->textures[SOUTH] = ft_strdup(line);
	else if (!line_check(line, 'E', 'A'))
		map->textures[EAST] = ft_strdup(line);
	else if (!line_check(line, 'W', 'E'))
		map->textures[WEST] = ft_strdup(line);
	else if (!line_check(line, 'F', ' '))
		map->textures[FLOOR] = ft_strdup(line);
	else if (!line_check(line, 'C', ' '))
		map->textures[CEILING] = ft_strdup(line);
	else if (!line_check(line, '\n', '\0'))
		return (0);
	else
		return (1);
	return (0);
}

static void	texture_truncate(t_game *game, char **textures)
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
				if (!line)
					error_and_exit("Error. Malloc failure.", game);
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

int	gettextures(t_game *game, int fd)
{
	char	*line;

	game->map.textures = malloc(7 * sizeof(char *));
	if (!game->map.textures)
		error_and_exit("Error. Malloc failure.", game);
	while (1)
	{
		line = get_next_line(fd);
		if (texture_strdup(&game->map, line))
		{
			free(line);
			return (1);
		}
		if (!line_check(line, 'C', ' '))
			break ;
		free(line);
	}
	if (line)
		free(line);
	line = NULL;
	game->map.textures[6] = NULL;
	if (!(game->map.textures[NORTH] && game->map.textures[SOUTH]
		&& game->map.textures[EAST] && game->map.textures[WEST]
		&& game->map.textures[FLOOR] && game->map.textures[CEILING]))
		return (1);
	texture_truncate(game, game->map.textures);
	return (0);
}
