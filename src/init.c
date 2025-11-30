#include "cub3d.h"


int	init_game(t_game *game, char *map_file)
{
	create_map(game, map_file);
	init_player_vectors(&game->player, &game->map);
	//mlx initialization
	//mlx window

	return (0);

}

static void	set_player_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = 0.66;
		player->plane.y = 0;
	}
	else if (dir == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = -0.66;
		player->plane.y = 0;
	}
	else if (dir == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = -0.66;
	}
}

void	init_player_vectors(t_player *player, t_map *map)
{
	//Check the init direction and intialize values. (NSEW)
	//adjust direction and FOV value
	//place the player in the middle of the grid by adding 0.5, to evade potential bugs (next to wall example)
	//in the end we want to replace the NSEW value into empty space ('0')!
}
