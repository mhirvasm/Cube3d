/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:58:49 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/12/22 16:07:43 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up_and_down(t_game *game)
{
	double		new_x;
	double		new_y;
	t_player	*p;

	p = &game->player;
	if (p->key_up)
	{
		new_x = p->pos.x + p->dir.x * MOVESPEED;
		new_y = p->pos.y + p->dir.y * MOVESPEED;
		if (!is_wall(game, new_x, p->pos.y))
			p->pos.x = new_x;
		if (!is_wall(game, p->pos.x, new_y))
			p->pos.y = new_y;
	}
	if (p->key_down)
	{
		new_x = p->pos.x - p->dir.x * MOVESPEED;
		new_y = p->pos.y - p->dir.y * MOVESPEED;
		if (!is_wall(game, new_x, p->pos.y))
			p->pos.x = new_x;
		if (!is_wall(game, p->pos.x, new_y))
			p->pos.y = new_y;
	}
}

void	move_right_and_left(t_game *game)
{
	double		new_x;
	double		new_y;
	t_player	*p;

	p = &game->player;
	if (p->key_right)
	{
		new_x = p->pos.x - p->dir.y * MOVESPEED;
		new_y = p->pos.y + p->dir.x * MOVESPEED;
		if (!is_wall(game, new_x, p->pos.y))
			p->pos.x = new_x;
		if (!is_wall(game, p->pos.x, new_y))
			p->pos.y = new_y;
	}
	if (p->key_left)
	{
		new_x = p->pos.x + p->dir.y * MOVESPEED;
		new_y = p->pos.y - p->dir.x * MOVESPEED;
		if (!is_wall(game, new_x, p->pos.y))
			p->pos.x = new_x;
		if (!is_wall(game, p->pos.x, new_y))
			p->pos.y = new_y;
	}
}
