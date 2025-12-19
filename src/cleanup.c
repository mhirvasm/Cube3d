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
	i = -1;
	if (map->textures)
	{
		while (map->textures[++i])
			free(map->textures[i]);
		free(map->textures);
	}
	if (map->line)
		free(map->line);
}

void	error_and_exit(char *msg, t_game *game)
{
	printf("%s\n", msg);
	if (game)
    {
		free_map(&game->map); //free map
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
    }
	exit(1);
}

void	error(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}
