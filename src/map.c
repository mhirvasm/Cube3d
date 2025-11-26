
#include "cub3d.h"

//strlen is -1 because we don't want the newline

void	create_map(char *file)
{
	t_map	*map;
	int		fd;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		error_and_exit("Error. Memory allocation failed", map);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_and_exit("Error. Invalid file", map);
	getmapsize(map, fd);
	create_grid(map, file);
	validate_grid(map);
	validate_path(map);
	printf("here5\n");
}

void	create_grid(t_map *map, char *file)
{
	int	fd;

	map->y = -1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_and_exit("Error. Invalid file", map);
	map->grid = malloc(map->height + 1 * sizeof(char *));
	if (!map->grid)
		error_and_exit("Error. Malloc failure", map);
	map->line = NULL;
	while (++map->y < map->height)
	{
		map->line = get_next_line(fd);
		map->grid[map->y] = ft_strdup(map->line);
		if (!map->grid[map->y])
			error_and_exit("Error. Strdup failure", map);
		map->grid[map->y][ft_strlen(map->grid[map->y]) - 1] = '\0';
		free(map->line);
	}
	map->grid[map->y] = NULL;
	close(fd);
}

void	validate_path(t_map *map)
{
	t_map	*copy;

	copy = ft_calloc(1, sizeof(t_map));
	if (!copy)
		error_and_exit("Error. Memory allocation failed", map);
	copy->y = -1;
	copy->grid = malloc(map->height + 1 * sizeof(char *));
	if (!copy->grid)
	{
		error_and_exit("Error. Memory allocation failed", map);
		free_map(copy);
	}
	while (++copy->y < map->height - 1)
	{
		copy->grid[copy->y] = ft_strdup(map->grid[copy->y]);
		if (!copy->grid[copy->y])
		{
			error_and_exit("Error. Strdup failure", map);
			free_map(copy);
		}
	}
	copy->grid[copy->y] = NULL;
	flood_fill(copy, map->playerx, map->playery);
	printf("here3\n");
	copy->y = -1;
	while (++copy->y < map->height - 1)
	{
		copy->x = -1;
		while (++copy->x < (int)ft_strlen(copy->grid[copy->y]) - 1)
		{
			if (copy->grid[copy->y][copy->x] != '1'
				&& copy->grid[copy->y][copy->x] != 'F')
				error_and_exit("Error. No valid path", copy);
		}
	}
	printf("here4\n");
	free_map(copy);
}

void	validate_grid(t_map *map)
{
	map->y = -1;
	while (++map->y < map->height - 1)
	{
		map->x = -1;
		while (++map->x < (int)ft_strlen(map->grid[map->y]) - 1)
		{
			wall_helper(map);
			validate_elements(map);
		}
	}
	count_elements(map);
}
