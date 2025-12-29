
#include "cub3d.h"

//strlen is -1 because we don't want the newline

void	create_map(t_game *game, char *map_file)
{
	t_map	*map_ptr;
	int		fd;

	map_ptr = &game->map; //Changing from mallocing, to use game struct straight away!

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_and_exit("Error. Invalid file1", game); //here we take game for cleanup
	if (gettextures(game, fd))
		error_and_exit("Error. Invalid file2.0", game);
	getmapsize(map_ptr, fd);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_and_exit("Error. Invalid file3", game);
	map_ptr->grid = malloc((map_ptr->height + 1) * sizeof(char *));
	if (!map_ptr->grid)
	{
		close(fd);
		error_and_exit("Error. Malloc failure", game);
	}
	create_grid(game, fd);
	validate_grid(game);
	validate_path(game);
	printf("Map created succesfully\n");
}

void	create_grid(t_game *game, int fd)
{
	t_map	*map;
	int		current_len; // new variable 

	map = &game->map;
	map->y = 0;
	map->width = 0; // initialize 
	while (1)
	{
		map->line = get_next_line(fd);
		if (!line_check(map->line, 'C', ' '))
			break ;
		free(map->line);
	}
	free(map->line);
	while (1)
	{
		map->line = get_next_line(fd);
		if (!line_check(map->line, '1', '1') || !line_check(map->line, '1', ' '))
		{
			printf(" found 1: %s and break\n", map->line);
			break ;
		}
		free(map->line);
	}
	while (map->y < map->height)
	{

		printf("map y = %d\n", map->height);
		if (map->y != 0)
			map->line = get_next_line(fd);
		//printf("%s\n", map->line);
		current_len = ft_strlen(map->line);
		if (map->line[current_len - 1] == '\n')
			current_len--; // substract the newline from len
		if (current_len > map->width)
			map->width = current_len;
		map->grid[map->y] = ft_strdup(map->line);
		if (!map->grid[map->y])
		{
			close(fd);
			error_and_exit("Error. Strdup failure", game);
		}
		map->grid[map->y][(int)ft_strlen(map->grid[map->y]) - 1] = '\0';
		free(map->line);
		map->line = NULL;
		map->y++;
	}
	map->grid[map->y] = NULL;
	close(fd);
}

void	validate_path(t_game *game)
{
	t_map	*copy;
	t_map	*map;
	int		x;
	int		y;

	map = &game->map;
	copy = malloc(1 * sizeof(t_map));
	if (!copy)
		error_and_exit("Error. Memory allocation failed", game);
	copy->height = map->height;
	copy->width = map->width;
	copy->textures = NULL;
	copy->line = NULL;
	copy->grid = malloc((map->height + 1) * sizeof(char *));
	if (!copy->grid)
	{
		free_map(copy);
		free(copy);
		error_and_exit("Error. Memory allocation failed", game);
	}
	y = 0;
	while (y < map->height)
	{
		copy->grid[y] = ft_strdup(map->grid[y]);
		if (!copy->grid[y])
		{
			free_map(copy);
			free(copy);
			error_and_exit("Error. Strdup failure", game);
		}
		y++;
	}
	copy->grid[y] = NULL;
	flood_fill(copy, map->playerx, map->playery);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (copy->grid[y][x])
		{
			if (copy->grid[y][x] == 'F')
			{
				if (x == 0 || y == 0 || y == map->height - 1 
					|| copy->grid[y][x + 1] == '\0' || copy->grid[y][x + 1] == ' ')
				{
					free_map(copy);
					free(copy);
					error_and_exit("Error. Map is not enclosed", game);
				}
			}
			x++;
		}
		y++;
	}
	free_map(copy);
	free(copy);
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
