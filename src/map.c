
#include "cub3d.h"

//strlen is -1 because we don't want the newline

void	create_map(t_game *game, char *map_file)
{
	t_map	*map_ptr;
	int		fd;

	map_ptr = &game->map; //Changing from mallocing, to use game struct straight away!

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_and_exit("Error. Invalid file", game); //here we take game for cleanup
	getmapsize(map_ptr, fd);
	create_grid(game, map_file);
	validate_grid(game);
	validate_path(game);
	printf("Map created succesfully\n");
}

void	create_grid(t_game *game, char *map_file)
{
	int		fd;
	t_map	*map;

	map = &game->map;
	map->y = 0;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_and_exit("Error. Invalid file", game);
	map->grid = malloc((map->height + 1) * sizeof(char *));
	if (!map->grid)
		error_and_exit("Error. Malloc failure", game);
	map->line = NULL;
	while (map->y < map->height)
	{
		map->line = get_next_line(fd);
		map->grid[map->y] = ft_strdup(map->line);
		if (!map->grid[map->y])
			error_and_exit("Error. Strdup failure", game);
		map->grid[map->y][(int)ft_strlen(map->grid[map->y]) - 1] = '\0';
		free(map->line);
		map->y++;
	}
	map->grid[map->y] = NULL;
	close(fd);
}

void	validate_path(t_game *game)
{
	t_map	*copy;
	t_map	*map;

	map = &game->map;
	map->y = 0;
	copy = ft_calloc(1, sizeof(t_map));
	if (!copy)
		error_and_exit("Error. Memory allocation failed", game);
	copy->grid = malloc(map->height + 1 * sizeof(char *));
	if (!copy->grid)
	{
		error_and_exit("Error. Memory allocation failed", game);
		free_map(copy);
	}
	while (map->y < map->height)
	{
		copy->grid[map->y] = ft_strdup(map->grid[map->y]);
		if (!copy->grid[map->y])
		{
			error_and_exit("Error. Strdup failure", game);
			free_map(copy);
		}
		map->y++;
	}
	copy->grid[map->y] = NULL;
	map->y = 0;
	flood_fill(copy, map->playerx, map->playery);
	printf("here3\n");
	map->y = 0;
	while (map->y < map->height - 1)
	{
		map->x = 0;
		while (map->x < (int)ft_strlen(copy->grid[map->y]) - 1)
		{
			if (copy->grid[map->y][map->x] != '1'
				&& copy->grid[map->y][map->x] != 'F')
				{
					free_map(copy);
					error_and_exit("Error. No valid path", game);
				}
			map->x++;
		}
		map->y++;
	}
	printf("here4\n");
	free_map(copy);
}

void	validate_grid(t_game *game)
{
	t_map *map;

	map = &game->map;
	map->y = 0;
	while (map->y < map->height - 1)
	{
		map->x = 0;
		while (map->x < (int)ft_strlen(map->grid[map->y]) - 1)
		{
			wall_helper(game);
			validate_elements(game);
			map->x++;
		}
		map->y++;
	}
	count_elements(game);
}
