/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:43:37 by vahdekiv          #+#    #+#             */
/*   Updated: 2026/01/02 08:51:02 by mhirvasm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_validation(t_game *game, int x, int y)
{
	t_map	*map;

	map = &game->map;
	if ((y == 0 && map->grid[y + 1][x] == '1'
		&& map->grid[y + 1][x + 1] != '1')
		|| (y == map->height - 1
		&& map->grid[y - 1][x] == '1'
		&& map->grid[y - 1][x - 1] != '1')
		|| (y != 0 && y != map->height - 1
		&& map->grid[y - 1][x] == '1'
		&& map->grid[y - 1][x + 1] != '1'
		&& map->grid[y + 1][x] == '1'
		&& map->grid[y + 1][x + 1] != '1'))
		error_and_exit("Error. Map not enclosed3", game);
}

void	texture_helper(char **textures, int i, int j, char *line)
{
	int	l;

	l = 0;
	while (textures[i][j])
		line[l++] = textures[i][j++];
	line[l - 1] = '\0';
	free(textures[i]);
	textures[i] = ft_strdup(line);
	free(line);
}

int	texture_validate(t_game *game, int fd)
{
	game->map.textures[6] = NULL;
	if (!game->map.textures[NORTH] || !game->map.textures[SOUTH]
		|| !game->map.textures[EAST] || !game->map.textures[WEST])
	{
		close(fd);
		return (1);
	}
	texture_truncate(game, game->map.textures, fd);
	get_colors(game, game->map.textures, fd);
	return (0);
}

void	grid(t_game *game, t_map *map, int fd)
{
	int	current_len;

	while (map->y < map->height)
	{
		if (map->y != 0)
			map->line = get_next_line(fd);
		current_len = ft_strlen(map->line);
		if (map->line[current_len - 1] == '\n')
			current_len--;
		if (current_len > map->width)
			map->width = current_len;
		map->grid[map->y] = ft_strdup(map->line);
		if (!map->grid[map->y])
		{
			close(fd);
			error_and_exit("Error. Strdup failure", game);
		}
		map->grid[map->y][(int)ft_strlen(map->grid[map->y]) - 1] = '\0';
		free(map->line);
		map->line = NULL;
		map->y++;
	}
	map->grid[map->y] = NULL;
	close(fd);
}

int	rgb_helper(t_game *game, char **rgb)
{
	int	r;
	int	g;
	int	b;
	int	color;

	r = -1;
	g = -1;
	b = -1;
	color = -1;
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
	{
		ft_free(rgb);
		error_and_exit("Invalid color values.", game);
	}
	color = encode_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	ft_free(rgb);
	return (color);
}
