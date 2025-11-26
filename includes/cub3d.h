#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line/get_next_line.h"

typedef struct s_map
{
	char	*line;
	int		height;
	int		y;
	int		x;
	int		playery;
	int		playerx;
	char	**grid;
	int		spawncount;
}	t_map;

typedef struct s_game
{
	t_map	*map;
}	t_game;

int		main(int argc, char **argv);
int		check_extension(char *argv);
void	create_map(char *file);
void	create_grid(t_map *map, char *file);
void	validate_path(t_map *map);
void	validate_grid(t_map *map);
void	getmapsize(t_map *map, int fd);
void	wall_helper(t_map *map);
void	validate_elements(t_map *map);
void	count_elements(t_map *map);
void	flood_fill(t_map *copy, int x, int y);
void	free_map(t_map *map);
void	error_and_exit(char *msg, t_map *map);
void	error(char *msg);

#endif
