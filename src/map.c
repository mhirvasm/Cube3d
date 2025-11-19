
#include "cub3d.h"

void	create_map(char *file)
{
	t_map	map;
	int		fd;

	map = ft_calloc(sizeof(t_map));
	if (!map)
		error_and_exit("Error. Memory allocation failed\n");
	fd = open(file, O_RDONLY);
	map.line = get_next_line(fd);
	map.width = ft_strlen(line);
	if (getmapsize(map, fd))
		error_and_exit("Error. Map size error\n");
	create_grid(map);
	player_pos(map);
	valid_path(map);
	validate_elements(map);
}

void	create_grid(t_map *map)
{

}

void	player_pos(t_map *map)
{

}

void	valid_path(t_map *map)
{

}

void	validate_elements(t_map *map)
{

}
