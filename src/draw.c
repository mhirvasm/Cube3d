/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 09:13:13 by mhirvasm          #+#    #+#             */
/*   Updated: 2026/01/02 09:19:25 by mhirvasm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	size = game->map.tile_size;
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1)
		{
			my_mlx_pixel_put(game, x * size + i, y * size + j, color);
			j++;
		}
		i++;
	}
}

static void	draw_line(t_game *game, t_vector start, t_vector end, int color)
{
	double	delta_x;
	double	delta_y;
	double	pixel_x;
	double	pixel_y;
	int		pixels;

	delta_x = end.x - start.x;
	delta_y = end.y - start.y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	if (pixels == 0)
		return ;
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = start.x;
	pixel_y = start.y;
	while (pixels)
	{
		my_mlx_pixel_put(game, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		pixels--;
	}
}

void	draw_player_dir(t_game *game, int tile_size)
{
	t_vector	start;
	t_vector	end;

	start.x = game->player.pos.x * tile_size;
	start.y = game->player.pos.y * tile_size;
	end.x = start.x + (game->player.dir.x * 30);
	end.y = start.y + (game->player.dir.y * 30);
	draw_line(game, start, end, 0xFFFF00);
}

void	draw_player(t_game *game, int tile_size)
{
	int	px;
	int	py;
	int	size;
	int	y;
	int	x;

	px = (int)(game->player.pos.x * tile_size);
	py = (int)(game->player.pos.y * tile_size);
	size = tile_size / 3;
	if (size < 2)
		size = 2;
	y = -size;
	while (y < size)
	{
		x = -size;
		while (x < size)
		{
			my_mlx_pixel_put(game, px + x, py + y, 0xFF0000);
			x++;
		}
		y++;
	}
}

void	draw_fov(t_game *game, int tile_size)
{
	int				x;
	t_ray			ray;
	t_vector		start;
	t_vector		end;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray, &game->player, x);
		perform_dda(game, &ray);
		start.x = game->player.pos.x * tile_size;
		start.y = game->player.pos.y * tile_size;
		end.x = ray.map.x * tile_size + (tile_size / 2);
		end.y = ray.map.y * tile_size + (tile_size / 2);
		draw_line(game, start, end, 0x00FF00);
		x += 50;
	}
}
