
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
	int		x; //lets use local variables
	int		y; // lets use local variables

	map = &game->map;
	//map->y = 0; we dont want to change these values DELETE THIS 
	copy = ft_calloc(1, sizeof(t_map));
	if (!copy)
		error_and_exit("Error. Memory allocation failed", game);
	copy->height = map->height; //lets copyy
	copy->width = map->width; //lets copyyyy
	copy->grid = malloc((map->height + 1) * sizeof(char *));
	if (!copy->grid)
	{
		free_map(copy); //free  before exit!!!
		error_and_exit("Error. Memory allocation failed", game);
	}
	y = 0;
	while (y < map->height)
	{
		copy->grid[y] = ft_strdup(map->grid[y]);
		if (!copy->grid[y])
		{
			free_map(copy); //free before exit
			error_and_exit("Error. Strdup failure", game);
		}
		y++;
	}
	copy->grid[y] = NULL;
	flood_fill(copy, map->playerx, map->playery);
	y = 0;
	while (y < map->height)
	{
		printf("%s\n", copy->grid[y]);
		y++;
	}
	printf("here3\n");
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (copy->grid[y][x])
		{
			// Check  if F is placed safely
			if (copy->grid[y][x] == 'F')
			{
				// If F is placed on any side of the map, --> map will leak, error!
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
	printf("hello\n");	
	// Clean,  free the copy, not used anymore 
//	free_map(copy);
//	free(copy);
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
