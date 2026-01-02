/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:48:20 by mhirvasm          #+#    #+#             */
/*   Updated: 2026/01/02 09:18:33 by mhirvasm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_2d_map(t_game *game)
{
	int	y;
	int	x;
	int	tile_size;

	game->map.tile_size = get_tile_size(game);
	tile_size = game->map.tile_size;
	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == '1')
				draw_square(game, x, y, WHITE);
			else if (game->map.grid[y][x] != ' ')
				draw_square(game, x, y, BLACK);
			x++;
		}
		y++;
	}
	draw_fov(game, tile_size);
	draw_player(game, tile_size);
	draw_player_dir(game, tile_size);
}

int	render_frame(t_game *game)
{
	move_player(game);
	if (DEBUG == 0)
	{
		raycast(game);
		draw_minimap(game);
	}
	if (DEBUG == 1)
	{
		draw_2d_map(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
