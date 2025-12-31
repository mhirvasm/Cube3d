/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:04:41 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/12/31 12:29:35 by mhirvasm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	line_check(char *line, char c, char d)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\f'
		|| line[i] == '\v' || line[i] == '\r')
		i++;
	if ((line[i] == c && line[i + 1] == d) || c == '\n')
		return (0);
	return (1);
}

static int	texture_strdup(t_map *map, char *line)
{
	if (!line_check(line, 'N', 'O'))
		map->textures[NORTH] = ft_strdup(line);
	if (!line_check(line, 'S', 'O'))
		map->textures[SOUTH] = ft_strdup(line);
	if (!line_check(line, 'E', 'A'))
		map->textures[EAST] = ft_strdup(line);
	if (!line_check(line, 'W', 'E'))
		map->textures[WEST] = ft_strdup(line);
	if (!line_check(line, 'F', ' '))
		map->textures[FLOOR] = ft_strdup(line);
	if (!line_check(line, 'C', ' '))
		map->textures[CEILING] = ft_strdup(line);
	else if (!line_check(line, '\n', '\0'))
		return (0);
	else
		return (1);
	return (0);
}

void	texture_truncate(t_game *game, char **textures, int fd)
{
	int		i;
	int		j;
	char	*line;

	i = -1;
	while (textures[++i] && i <= 3)
	{
		j = 0;
		while (textures[i][j])
		{
			if (textures[i][j] == '.')
			{
				line = malloc((ft_strlen(textures[i]) - j) * sizeof(char));
				if (!line)
				{
					close(fd);
					error_and_exit("Error. Malloc failure.", game);
				}
				texture_helper(textures, i, j, line);
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
	{
		close(fd);
		error_and_exit("Error. Malloc failure.", game);
	}
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
	if (texture_validate(game, fd))
		return (1);
	return (0);
}
