/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:58:22 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/12/31 12:18:21 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	getmapsize(t_map *map, int fd)
{
	map->height = 0;
	map->line = NULL;
	while (1)
	{
		map->line = get_next_line(fd);
		if (!line_check(map->line, '1', '1')
			|| !line_check(map->line, '1', ' '))
			break ;
		free(map->line);
	}
	map->height++;
	free(map->line);
	while (1)
	{
		map->line = get_next_line(fd);
		if (!map->line)
			break ;
		map->height++;
		free(map->line);
	}
	close(fd);
}

void	wall_helper(t_game *game)
{
	t_map	*map;

	map = &game->map;
	while (map->grid[map->y][map->x] == ' ')
	{
		if (map->y == 0 && (map->grid[map->y + 1][map->x] != ' '
			&& map->grid[map->y + 1][map->x] != '1'))
			error_and_exit("Error. Map not enclosed1", game);
		if (map->y == map->height - 1 && (map->grid[map->y - 1][map->x] != ' '
			|| map->grid[map->y - 1][map->x] != '1'))
			error_and_exit("Error. Map not enclosed2", game);
		if (map->y != 0 && map->y != map->height - 1
			&& ((map->grid[map->y - 1][map->x] != ' '
				&& map->grid[map->y - 1][map->x] != '1')
			|| (map->grid[map->y + 1][map->x] != ' '
			&& map->grid[map->y + 1][map->x] != '1')))
			error_and_exit("Error. Map not enclosed2.1", game);
		map->x++;
	}
}

void	validate_elements(t_game *game)
{
	t_map	*map;

	map = &game->map;
	if ((map->y == 0 || map->y == map->height - 1)
		&& (map->grid[map->y][map->x] != '1'
		&& map->grid[map->y][map->x] != ' '))
		error_and_exit("Error. Map not enclosed4", game);
	if (map->grid[map->y][map->x] && map->grid[map->y][map->x] != '1'
		&& map->grid[map->y][map->x] != '0'
		&& map->grid[map->y][map->x] != 'N'
		&& map->grid[map->y][map->x] != 'W'
		&& map->grid[map->y][map->x] != 'E'
		&& map->grid[map->y][map->x] != 'S')
		error_and_exit("Error. Invalid elements1", game);
	if ((map->x == 0 && map->grid[map->y][map->x] != ' '
		&& map->grid[map->y][map->x] != '1')
		|| ((map->x != 0 && map->grid[map->y][map->x - 1]
		&& map->grid[map->y][map->x - 1] == ' '
		&& (map->grid[map->y][map->x] != ' '
		&& map->grid[map->y][map->x] != '1'))
		|| map->grid[map->y][ft_strlen(map->grid[map->y]) - 1] != '1'))
		error_and_exit("Error. Map not enclosed5", game);
}

void	count_elements(t_game *game)
{
	t_map	*map;

	map = &game->map;
	map->spawncount = 0;
	map->y = -1;
	while (++map->y < map->height - 1)
	{
		map->x = -1;
		while (++map->x < (int)ft_strlen(map->grid[map->y]) - 1)
		{
			if (map->grid[map->y][map->x] == 'N'
				|| map->grid[map->y][map->x] == 'S'
				|| map->grid[map->y][map->x] == 'W'
				|| map->grid[map->y][map->x] == 'E')
			{
				map->spawncount++;
				map->playery = map->y;
				map->playerx = map->x;
				map->player_dir = map->grid[map->y][map->x];
			}
		}
	}
	if (map->spawncount != 1)
		error_and_exit("Error. Invalid elements2", game);
}

void	flood_fill(t_map *copy, int x, int y)
{
	if (y < 0 || y >= copy->height)
		return ;
	if (x < 0 || x >= (int)ft_strlen(copy->grid[y]))
		return ;
	if (copy->grid[y][x] == 'F' || copy->grid[y][x] == '1')
		return ;
	copy->grid[y][x] = 'F';
	flood_fill(copy, x + 1, y);
	flood_fill(copy, x - 1, y);
	flood_fill(copy, x, y + 1);
	flood_fill(copy, x, y - 1);
}
