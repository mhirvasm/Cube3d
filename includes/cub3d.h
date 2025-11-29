#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft.h"
# include "get_next_line/get_next_line.h"

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define DEBUG 0

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define KEY_ESC 65307

# define PI 3.14159265359
# define MOVESPEED 0.1
# define ROTSPEED 0.05



typedef struct s_vector
{
    double x;
    double y;
} t_vector;

typedef struct s_int_point
{
    int x;
    int y;
} t_point;

typedef struct s_ray
{
    t_vector    direction;  // Direction of the ray
    t_vector    side_dist;  // distance to next line
    t_vector    delta_dist; // distance over one square (fixed value)
    t_point     map;        // current screen
    t_point     step;       // direction (1 or -1)
    double      wall_dist;  // final distance
    int         side;       // (flag) 0 = vertical wall, 1 for horizontal
} t_ray;

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

typedef struct s_player
{
    t_vector    pos;    //precise location
    t_vector    dir;    // direction vector
    t_vector    plane;  // cameraplane vector (FOV)

    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;

    bool left_rotate;
    bool right_rotate;
}   t_player;

typedef struct s_game
{
	t_map	*map;

	void *mlx;
    void *win;
    void *img;

    char *data;
    int bpp;
    int size_line;
    int endian;

    t_player player;
}	t_game;

//TODO break prototypes in subcategories
int		main(int argc, char **argv);
int		check_extension(char *argv);
void	create_map(t_game game, char *map_file);
void	create_grid(t_map *map, char *map_file);
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
int	    init_game(t_game *game, char *map_file);

#endif
