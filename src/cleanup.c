#include "cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	i = -1;
	if (map->grid)
	{
		while (map->grid[++i])
			free(map->grid[i]);
		free(map->grid);
	}
	if (map)
		free(map);
}

void	error_and_exit(char *msg, t_map *map)
{
	printf("%s\n", msg);
	if (map)
		free_map(map);
	exit(0);
}

void	error(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}
