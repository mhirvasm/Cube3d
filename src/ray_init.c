/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:09:51 by mhirvasm          #+#    #+#             */
/*   Updated: 2025/12/22 12:33:09 by mhirvasm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_game *game)
{
	t_ray	ray;
	int		x;

	ft_bzero(&ray, sizeof(t_ray));
	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray, &game->player, x);
		perform_dda(game, &ray);
		calculate_wall_dist(&ray);
		draw_walls(game, x, &ray);
		x++;
	}
}
static void get_delta_dist(t_ray *ray)
{
    if (ray->direction.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1.0 / ray->direction.x);
	if (ray->direction.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1.0 / ray->direction.y);
}

static void get_side_dist(t_ray *ray, t_player *player)
{
    if (ray->direction.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - player->pos.x)
			* ray->delta_dist.x;
	}
	if (ray->direction.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - player->pos.y)
			* ray->delta_dist.y;
	}
}
void	init_ray(t_ray *ray, t_player *player, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->direction.x = player->dir.x + (player->plane.x * camera_x);
	ray->direction.y = player->dir.y + (player->plane.y * camera_x);
	ray->map.x = (int)player->pos.x;
	ray->map.y = (int)player->pos.y;
	get_delta_dist(ray);
    get_side_dist(ray, player);
}

void	perform_dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!!!hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (game->map.grid[ray->map.y][ray->map.x] == '1')
			hit = 1;
	}
}

void	calculate_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->wall_dist = (ray->side_dist.y - ray->delta_dist.y);
	ray->line_height = (int)(HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

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

void	draw_walls(t_game *game, int x, t_ray *ray)
{
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;
	char	*pixel;

	tex_num = get_texture_index(ray);
	if (ray->side == 0)
		wall_x = game->player.pos.y + ray->wall_dist * ray->direction.y;
	else
		wall_x = game->player.pos.x + ray->wall_dist * ray->direction.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)game->walls[tex_num].width);
	step = 1.0 * game->walls[tex_num].height / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(game, x, y, game->ceiling_color);
		y++;
	}
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (game->walls[tex_num].height - 1);
		tex_pos += step;
		pixel = game->walls[tex_num].addr
			+ (tex_y * game->walls[tex_num].size_line
				+tex_x * (game->walls[tex_num].bpp / 8));
		color = *(unsigned int *)pixel;
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
	y = ray->draw_end;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(game, x, y, game->floor_color);
		y++;
	}
}
