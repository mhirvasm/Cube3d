/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 09:08:03 by mhirvasm          #+#    #+#             */
/*   Updated: 2026/01/02 09:19:17 by mhirvasm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->direction.x < 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (ray->direction.y < 0)
			return (NORTH);
		else
			return (SOUTH);
	}
}

static void	init_wall_vars(t_game *game, t_ray *ray, t_wall_vars *v)
{
	v->tex_num = get_texture_index(ray);
	if (ray->side == 0)
		v->wall_x = game->player.pos.y + ray->wall_dist * ray->direction.y;
	else
		v->wall_x = game->player.pos.x + ray->wall_dist * ray->direction.x;
	v->wall_x -= floor(v->wall_x);
	v->tex_x = (int)(v->wall_x * (double)game->walls[v->tex_num].width);
	if ((ray->side == 0 && ray->direction.x > 0)
		|| (ray->side == 1 && ray->direction.y < 0))
		v->tex_x = game->walls[v->tex_num].width - v->tex_x - 1;
	v->step = 1.0 * game->walls[v->tex_num].height / ray->line_height;
	v->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* v->step;
}

static void	draw_stripe(t_game *game, int x, t_ray *ray, t_wall_vars *v)
{
	int		y;
	int		color;
	char	*src;

	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(game, x, y, game->ceiling_color);
		y++;
	}
	while (y < ray->draw_end)
	{
		v->tex_y = (int)v->tex_pos & (game->walls[v->tex_num].height - 1);
		v->tex_pos += v->step;
		src = game->walls[v->tex_num].addr + (v->tex_y
				* game->walls[v->tex_num].size_line + v->tex_x
				* (game->walls[v->tex_num].bpp / 8));
		color = *(unsigned int *)src;
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(game, x, y++, game->floor_color);
	}
}

void	draw_walls(t_game *game, int x, t_ray *ray)
{
	t_wall_vars	vars;

	init_wall_vars(game, ray, &vars);
	draw_stripe(game, x, ray, &vars);
}
