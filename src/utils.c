/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 13:48:57 by vahdekiv          #+#    #+#             */
/*   Updated: 2026/01/02 09:18:41 by mhirvasm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	textures_init(t_game *game, int fd)
{
	game->map.textures = malloc(7 * sizeof(char *));
	if (!game->map.textures)
	{
		close(fd);
		error_and_exit("Error. Malloc failure.", game);
	}
	game->map.textures[NORTH] = NULL;
	game->map.textures[SOUTH] = NULL;
	game->map.textures[WEST] = NULL;
	game->map.textures[EAST] = NULL;
	game->map.textures[FLOOR] = NULL;
	game->map.textures[CEILING] = NULL;
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->data + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}
