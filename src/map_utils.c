
#include "cub3d.h"

void	getmapsize(t_map *map, int fd)
{
	while (1)
	{
		map.line = get_next_line(fd);
		if (!map.line)
			break ;
		map.height++;
		free(map.line);
	}
	close(fd);
}

void	validate_elements(t_map *map)
{
	if ((map->y == 0 || map->y == map->height)
		&& map->grid[map->y][map->x] != '1')
		error_and_exit("Error. Map not enclosed\n", map);
	if (map->grid[map->y][map->x] != '1'
		|| map->grid[map->y][map->x] != '0'
		|| map->grid[map->y][map->x] != 'N'
		|| map->grid[map->y][map->x] != 'W'
		|| map->grid[map->y][map->x] != 'E'
		|| map->grid[map->y][map->x] != 'S'
		|| map->grid[map->y][map->x] != ' ')
		error_and_exit("Error. Invalid elements\n", map);
	if ((map->grid[map->y][map->x - 1] == ' '
		&& (map->grid[map->y][map->x] != ' '
		|| map->grid[map->y][map->x] != '1'))
		|| map->grid[map->y][ft_strlen(map->grid) - 1] != '1'
		|| (map->x == 0 && map->grid[map->y][map->x] != ' '
		&& map->grid[map->y][map->x] != '1'))
		error_and_exit("Error. Map not enclosed\n", map);
}

void	count_elements(t_map *map)
{
	map->spawncount = 0;
	map->y = -1;
	while (++map->y < map->height)
	{
		map->x = -1;
		while (++map->x < ft_strlen(map.grid[map->y] - 1))
		{
			if (map->grid[map->y][map->x] == 'N'
				|| map->grid[map->y][map->x] == 'S'
				|| map->grid[map->y][map->x] == 'W'
				|| map->grid[map->y][map->x] == 'E')
			{
				map->spawncount++;
				map->playery = map->y;
				map->playerx = map->x;
			}
		}
	}
}

void	flood_fill(t_map *copy, int x, int y)
{
	if (copy->grid[y][x] == 'F' || copy->grid[y][x] == '1')
		return ;
	copy->grid[y][x] = 'F';
	flood_fill(copy, x - 1, y);
	flood_fill(copy, x + 1, y);
	flood_fill(copy, x, y - 1);
	flood_fill(copy, x, y + 1);
}
