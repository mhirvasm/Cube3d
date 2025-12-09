#include "cub3d.h"

static void init_graphics(t_game *game)
{
	//mlx initialization
	game->mlx = mlx_init();
	if (!game->mlx)
		error_and_exit("Error. MLX init failed", game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		error_and_exit("Error. Window creation failed", game);

	// Creating "empty iamge" where we do our "drawing"
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		error_and_exit("Error. Image creation failed", game);  //TODO REMEMBER CLEANUP

	// Get the data address of the picture so we can modify it!
	// bpp = bytes per pixel (usually 32)
	// size_line = width of one line of pixels
	// endian = bit order? dont really understand this throughout,  but we shouldnt need  to stress about this
	// we dont need to initialize  these values, the function  will write the correct values into them!
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->data)
		error_and_exit("Error. Image data fetch failed", game); //TODO REMEMBER CLEANUP
	//TODO put_pixel function
}

int	init_game(t_game *game, char *map_file)
{
	create_map(game, map_file);
	init_player_vectors(&game->player, &game->map);
	init_graphics(game);
	return (0);

}
/*
static void	set_player_direction(t_map *map, t_player *player)
{
	//TODO how to make this into 25 lines? HNGGGHGHGHGHG
	if (map->player_dir == 'N')
		player->angle = (PI / 180) * 270; // facing north
	else if (map->player_dir == 'S')
		player->angle = (PI / 180) * 90; // facing south
	else if (map->player_dir == 'E')
		player->angle = 0; // facing east
	else if (map->player_dir == 'W')
		player->angle = (PI / 180) * 180; // facing west
}*/

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
	//init and place the player in the middle of the grid by adding 0.5, to evade potential bugs (next to wall example)
	player->pos.x = (double)map->playerx + 0.5;
	player->pos.y = (double)map->playery + 0.5; //"playery" lmao xdd
	set_player_direction(player, map->player_dir);
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
	//Check the init direction and intialize values. (NSEW) 
	//adjust direction and FOV value

	//in the end we want to replace the NSEW value into empty space ('0')!
	map->grid[map->playery][map->playerx] = '0';
}
