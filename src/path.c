/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:07:42 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/12/22 15:33:55 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	grid_copy(t_game *game, t_map *copy)
{
	t_map	*map;
	int		y;

	map = &game->map;
	y = 0;
	while (y < map->height)
	{
		copy->grid[y] = ft_strdup(map->grid[y]);
		if (!copy->grid[y])
		{
			free_map(copy);
			free(copy);
			error_and_exit("Error. Strdup failure", game);
		}
		y++;
	}
	copy->grid[y] = NULL;
	flood_fill(copy, map->playerx, map->playery);
}

void	validate_copy(t_game *game, t_map *copy, int x, int y)
{
	t_map	*map;

	map = &game->map;
	while (y < map->height)
	{
		x = 0;
		while (copy->grid[y][x])
		{
			if (copy->grid[y][x] == 'F')
			{
				if (x == 0 || y == 0 || y == map->height - 1
					|| copy->grid[y][x + 1] == '\0'
					|| copy->grid[y][x + 1] == ' ')
				{
					free_map(copy);
					free(copy);
					error_and_exit("Error. Map is not enclosed", game);
				}
			}
			x++;
		}
		y++;
	}
	free_map(copy);
	free(copy);
}
