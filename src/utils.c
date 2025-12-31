/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 13:48:57 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/12/31 13:57:33 by vahdekiv         ###   ########.fr       */
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
