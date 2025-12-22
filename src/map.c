/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:15:10 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/12/22 15:36:52 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_map(t_game *game, char *map_file)
{
	t_map	*map_ptr;
	int		fd;

	map_ptr = &game->map;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_and_exit("Error. Invalid file1", game);
	if (gettextures(game, fd))
		error_and_exit("Error. Invalid file2.0", game);
	getmapsize(map_ptr, fd);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_and_exit("Error. Invalid file3", game);
	map_ptr->grid = malloc((map_ptr->height + 1) * sizeof(char *));
	if (!map_ptr->grid)
	{
		close(fd);
		error_and_exit("Error. Malloc failure", game);
	}
	create_grid(game, fd);
	validate_grid(game);
	validate_path(game);
	printf("Map created succesfully\n");
}

void	create_grid(t_game *game, int fd)
{
	t_map	*map;

	map = &game->map;
	map->y = 0;
	map->width = 0;
	while (1)
	{
		map->line = get_next_line(fd);
		if (!line_check(map->line, 'C', ' '))
			break ;
		free(map->line);
	}
	free(map->line);
	while (1)
	{
		map->line = get_next_line(fd);
		if (line_check(map->line, '1', '1'))
			break ;
		free(map->line);
	}
	grid(game, map, fd);
}

void	validate_path(t_game *game)
{
	t_map	*copy;
	t_map	*map;
	int		x;
	int		y;

	y = 0;
	x = 0;
	map = &game->map;
	copy = malloc(1 * sizeof(t_map));
	if (!copy)
		error_and_exit("Error. Memory allocation failed", game);
	copy->height = map->height;
	copy->width = map->width;
	copy->textures = NULL;
	copy->line = NULL;
	copy->grid = malloc((map->height + 1) * sizeof(char *));
	if (!copy->grid)
	{
		free_map(copy);
		free(copy);
		error_and_exit("Error. Memory allocation failed", game);
	}
	grid_copy(game, copy);
	validate_copy(game, copy, x, y);
}

void	validate_grid(t_game *game)
{
	t_map	*map;

	map = &game->map;
	map->y = 0;
	while (map->y < map->height - 1)
	{
		map->x = 0;
		while (map->x < (int)ft_strlen(map->grid[map->y]) - 1)
		{
			wall_helper(game);
			validate_elements(game);
			map->x++;
		}
		map->y++;
	}
	count_elements(game);
}
