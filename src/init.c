/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 09:09:04 by mhirvasm          #+#    #+#             */
/*   Updated: 2025/12/19 13:57:02 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_and_exit("Error. MLX init failed", game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		error_and_exit("Error. Window creation failed", game);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		error_and_exit("Error. Image creation failed", game);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->data)
		error_and_exit("Error. Image data fetch failed", game);
}
/*
static void init_textures(t_game *game)
{
	int	i;

	i = 0;
	
	while (i < 4) // NORTH EAST SOUTH WEST = 4 
	{
    game->walls[i].img = mlx_xpm_file_to_image(game->mlx, 
                         game->map.textures[i],
                         &game->walls[i].width, 
                         &game->walls[i].height);

    if (!game->walls[i].img)
        error_and_exit("Error. Texture load failed", game);

    game->walls[i].addr = mlx_get_data_addr(game->walls[i].img,
                          &game->walls[i].bpp,
                          &game->walls[i].size_line,
                          &game->walls[i].endian);
	}

}*/

int	init_game(t_game *game, char *map_file)
{
	create_map(game, map_file);
	init_player_vectors(&game->player, &game->map);
	init_graphics(game);
//	init_textures(game);
	return (0);
}

static void	set_player_direction(t_player *player, char dir)
{
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	if (dir == 'N')
	{
		player->dir.y = -1;
		player->plane.x = 0.66;
	}
	else if (dir == 'S')
	{
		player->dir.y = 1;
		player->plane.x = -0.66;
	}
	else if (dir == 'E')
	{
		player->dir.x = 1;
		player->plane.y = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir.x = -1;
		player->plane.y = -0.66;
	}
}

void	init_player_vectors(t_player *player, t_map *map)
{
	player->pos.x = (double)map->playerx + 0.5;
	player->pos.y = (double)map->playery + 0.5;
	set_player_direction(player, map->player_dir);
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
	map->grid[map->playery][map->playerx] = '0';
}
