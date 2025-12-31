/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:09:16 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/12/31 14:24:25 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	i = -1;
	if (map->grid)
	{
		while (map->grid[++i])
			free(map->grid[i]);
		free(map->grid);
	}
	if (map->textures)
	{
		free(map->textures[NORTH]);
		free(map->textures[SOUTH]);
		free(map->textures[WEST]);
		free(map->textures[EAST]);
		free(map->textures[FLOOR]);
		free(map->textures[CEILING]);
		free(map->textures);
	}
	if (map->line)
		free(map->line);
}

void	error_and_exit(char *msg, t_game *game)
{
	printf("%s\n", msg);
	if (game)
	{
		free_map(&game->map);
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
	}
	exit(1);
}

void	error(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}
