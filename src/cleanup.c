#include "cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->grid)
    {
        while (map->grid[i])
        {
            free(map->grid[i]);
            map->grid[i] = NULL; // countering double frees
            i++;
        }
        free(map->grid);
        map->grid = NULL;
    }
    if (map->line)
    {
        free(map->line);
        map->line = NULL;
    }
	//dont free the map	here, its part of game
}

void	error_and_exit(char *msg, t_game *game)
{
	printf("%s\n", msg);
	if (game)
		free_map(&game->map); //free map
	//TODO add mlx cleanup here too behind if check
	exit(1);
}

void	error(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}
