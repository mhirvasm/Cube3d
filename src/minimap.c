/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 09:14:38 by mhirvasm          #+#    #+#             */
/*   Updated: 2026/01/02 09:19:45 by mhirvasm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;

	pixel_x = MM_OFFSET_X + (x * MM_TILE);
	pixel_y = MM_OFFSET_Y + (y * MM_TILE);
	i = 0;
	while (i < MM_TILE)
	{
		j = 0;
		while (j < MM_TILE)
		{
			my_mlx_pixel_put(game, pixel_x + j, pixel_y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_player(t_game *game)
{
	int	center_x;
	int	center_y;
	int	i;
	int	j;

	center_x = MM_OFFSET_X + (MM_VIEW_DIST * MM_TILE) + (MM_TILE / 2);
	center_y = MM_OFFSET_Y + (MM_VIEW_DIST * MM_TILE) + (MM_TILE / 2);
	i = -2;
	while (i < 2)
	{
		j = -2;
		while (j < 2)
		{
			my_mlx_pixel_put(game, center_x + j, center_y + i, RED);
			j++;
		}
		i++;
	}
}

static int	get_minimap_color(t_game *game, int map_x, int map_y)
{
	if (map_y < 0 || map_y >= game->map.height || map_x < 0
		|| map_x >= (int)ft_strlen(game->map.grid[map_y]))
		return (0x222222);
	if (game->map.grid[map_y][map_x] == '1')
		return (WHITE);
	if (game->map.grid[map_y][map_x] != ' ')
		return (BLACK);
	return (0x222222);
}

void	draw_minimap(t_game *game)
{
	int	y;
	int	x;
	int	map_y;
	int	map_x;
	int	color;

	y = -MM_VIEW_DIST;
	while (y <= MM_VIEW_DIST)
	{
		x = -MM_VIEW_DIST;
		while (x <= MM_VIEW_DIST)
		{
			map_y = (int)game->player.pos.y + y;
			map_x = (int)game->player.pos.x + x;
			color = get_minimap_color(game, map_x, map_y);
			draw_minimap_square(game, x + MM_VIEW_DIST, y + MM_VIEW_DIST,
				color);
			x++;
		}
		y++;
	}
	draw_minimap_player(game);
}

int	get_tile_size(t_game *game)
{
	int	scale_w;
	int	scale_h;
	int	tile_size;

	scale_w = WIDTH / game->map.width;
	scale_h = HEIGHT / game->map.height;
	if (scale_w < scale_h)
		tile_size = scale_w;
	else
		tile_size = scale_h;
	if (tile_size < 1)
		tile_size = 1;
	return (tile_size);
}
