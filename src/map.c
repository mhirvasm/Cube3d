
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
	create_grid(map_ptr, map_file);
	validate_grid(map_ptr);
	validate_path(map_ptr);
	printf("here5\n");
}

void	create_grid(t_map *map, char *map_file)
{
	int	fd;

	map->y = 0;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_and_exit("Error. Invalid file", map);
	map->grid = malloc((map->height + 1) * sizeof(char *));
	if (!map->grid)
		error_and_exit("Error. Malloc failure", map);
	map->line = NULL;
	while (map->y < map->height)
	{
		map->line = get_next_line(fd);
		map->grid[map->y] = ft_strdup(map->line);
		if (!map->grid[map->y])
			error_and_exit("Error. Strdup failure", map);
		map->grid[map->y][(int)ft_strlen(map->grid[map->y]) - 1] = '\0';
		free(map->line);
		map->y++;
	}
	map->grid[map->y] = NULL;
	close(fd);
}

void	validate_path(t_map *map)
{
	t_map	*copy;

	map->y = 0;
	copy = ft_calloc(1, sizeof(t_map));
	if (!copy)
		error_and_exit("Error. Memory allocation failed", map);
	copy->grid = malloc(map->height + 1 * sizeof(char *));
	if (!copy->grid)
	{
		error_and_exit("Error. Memory allocation failed", map);
		free_map(copy);
	}
	while (map->y < map->height)
	{
		copy->grid[map->y] = ft_strdup(map->grid[map->y]);
		if (!copy->grid[map->y])
		{
			error_and_exit("Error. Strdup failure", map);
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
				error_and_exit("Error. No valid path", copy);
			copy->x++;
		}
		copy->y++;
	}
	printf("here4\n");
	free_map(copy);
}

void	validate_grid(t_map *map)
{
	map->y = 0;
	while (map->y < map->height - 1)
	{
		map->x = 0;
		while (map->x < (int)ft_strlen(map->grid[map->y]) - 1)
		{
			wall_helper(map);
			validate_elements(map);
			map->x++;
		}
		map->y++;
	}
	count_elements(map);
}
