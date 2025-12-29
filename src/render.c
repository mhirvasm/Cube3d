/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:48:20 by mhirvasm          #+#    #+#             */
/*   Updated: 2025/12/29 11:58:26 by mhirvasm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->data + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

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

static void	draw_player_dir(t_game *game, int tile_size)
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

static void	draw_fov(t_game *game, int tile_size)
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

static int	get_tile_size(t_game *game)
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

void	draw_2d_map(t_game *game)
{
	int	y;
	int x;
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
