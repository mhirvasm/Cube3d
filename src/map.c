
#include "cub3d.h"

//strlen is -1 because we don't want the newline

void	create_map(char *file)
{
	t_map	map;
	int		fd;

	map = ft_calloc(sizeof(t_map));
	if (!map)
		error_and_exit("Error. Memory allocation failed\n", &map);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_and_exit("Error. Invalid file\n", &map);
	map.line = get_next_line(fd);
	map.width = ft_strlen(line - 1);
	map.height = 1;
	free(map.line);
	getmapsize(&map, fd);
	create_grid(&map, file);
	validate_grid(&map);
	valid_path(&map);
}

void	create_grid(t_map *map, char *file)
{
	int	fd;

	map->y = -1;
	map->grid = malloc(map->height + 1 * sizeof(char *));
	if (!map->grid)
		error_and_exit("Error. Malloc failure\n", map);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_and_exit("Error. Invalid file\n", map);
	while (++map->y < map->height)
	{
		map->line = get_next_line(fd);
		map->grid[map->y] = ft_strdup(map->line);
		if (!map->grid[map->y])
			error_and_exit("Error. Strdup failure\n", map);
		map->grid[map->y][ft_strlen(map->grid) - 1] = '\0';
		free(map->line);
	}
	map->grid[map->y] = '\0';
	close(fd);
}

void	valid_path(t_map *map)
{
//copy map
//flood fill
}

void	validate_grid(t_map *map)
{
	map->y = -1;
	while (++map->y < map->height)
	{
		map->x = -1;
		while (++map->x < ft_strlen(map.grid[map->y] - 1))
		{
			while (map->grid[map->y][map->x] == ' ')
				map->x++;
			validate_elements(map);
		}
	}
	count_elements(map);
}
