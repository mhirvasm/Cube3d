#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# include <mlx.h>
# include "libft.h"
# include "get_next_line/get_next_line.h"

# define WIDTH 1980
# define HEIGHT 1280
# define BLOCK 32
# define DEBUG 0

# define WHITE 0xFFFFFF
# define BLACK 0x000000

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define KEY_ESC 65307

# define PI 3.14159265359
# define MOVESPEED 0.02
# define ROTSPEED 0.01

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define FLOOR 4
# define CEILING 5


typedef struct s_vector
{
    float x;
    float y;
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
    int     width;
	int		y;
	int		x;
	int		playery;
	int		playerx;
	char	**grid;
	char	player_dir;
	int		spawncount;
	char	**textures;
}	t_map;

typedef struct s_player
{
    t_vector    pos;    //precise location
    t_vector    dir;    // direction vector
    t_vector    plane;  // cameraplane vector (FOV)
	float		angle;
    bool		key_up;
    bool		key_down;
    bool		key_left;
    bool		key_right;
    bool		left_rotate;
    bool		right_rotate;
}   t_player;

typedef struct s_game
{
	t_map	map;

	void	*mlx;
    void	*win;
    void	*img;

    char	*data;
    int		bpp;
    int		size_line;
    int		endian;

    t_player player;
}	t_game;

/* ************************************************************************** */
/* INITIALIZATION                                                             */
/* ************************************************************************** */
int     init_game(t_game *game, char *map_file);
void    init_player_vectors(t_player *player, t_map *map);

/* ************************************************************************** */
/* MAP PARSING & READING                                                      */
/* ************************************************************************** */
int     check_extension(char *argv);
int		gettextures(t_game *game, int fd);
int		line_check(char *line, char c, char d);
void    create_map(t_game *game, char *map_file);
void    create_grid(t_game *game, int fd);
void    getmapsize(t_map *map, int fd);

/* ************************************************************************** */
/* MAP VALIDATION                                                             */
/* ************************************************************************** */
void    validate_grid(t_game *game);
void    validate_path(t_game *game);
void    wall_helper(t_game *game);
void    validate_elements(t_game *game);
void    count_elements(t_game *game);
void    flood_fill(t_map *copy, int x, int y);

/* ************************************************************************** */
/* RENDERING & GRAPHICS                                                       */
/* ************************************************************************** */
int     render_frame(t_game *game);
void    draw_2d_map(t_game *game);
void    draw_player(t_game *game);
void	draw_square(t_game *game, int x, int y, int color);
void	clear_image(t_game *game);
void    my_mlx_pixel_put(t_game *game, int x, int y, int color);
void    init_ray(t_game *game);

/* ************************************************************************** */
/* INPUT & MOVEMENT                                                           */
/* ************************************************************************** */
int     key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	move_player(t_game *game);
void	rotate_player(t_game *game, double rot_speed);

/* ************************************************************************** */
/* CLEANUP & ERROR HANDLING                                                   */
/* ************************************************************************** */
void    free_map(t_map *map);
void    error_and_exit(char *msg, t_game *game);
void    error(char *msg);

#endif
