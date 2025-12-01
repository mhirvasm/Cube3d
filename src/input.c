#include "cub3d.h"

//rotate player function
void	rotate_player(t_game *game, double rot_speed)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;

	p = &game->player;
	old_dir_x = p->dir.x;
	p->dir.x = p->dir.x * cos(rot_speed) - p->dir.y * sin(rot_speed);
	p->dir.y = old_dir_x * sin(rot_speed) + p->dir.y * cos(rot_speed);
	old_plane_x = p->plane.x;
	p->plane.x = p->plane.x * cos(rot_speed) - p->plane.y * sin(rot_speed);
	p->plane.y = old_plane_x * sin(rot_speed) + p->plane.y * cos(rot_speed);
}

static int	movement(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == '1')
		return (1);
	return (0);
}
//key hooks, for moving and changind direction
int	key_hook(int keycode, t_game *game)
{
	int x;
	int	y;

	x = game->player.pos.x;
	y = game->player.pos.y;
	if (keycode == KEY_ESC)
		error_and_exit("Game closed", game);

	// Moving W S 
	if (keycode == W)
	{
		x += game->player.dir.x * MOVESPEED;
		y += game->player.dir.y * MOVESPEED;
		if (movement(game, x, y))
			return (0);
		game->player.pos.x += game->player.dir.x * MOVESPEED;
		game->player.pos.y += game->player.dir.y * MOVESPEED;
	}
	if (keycode == S)
	{
		x -= game->player.dir.x * MOVESPEED;
		y -= game->player.dir.y * MOVESPEED;
		if (movement(game, x, y))
			return (0);
		game->player.pos.x -= game->player.dir.x * MOVESPEED;
		game->player.pos.y -= game->player.dir.y * MOVESPEED;
		movement(game, game->player.pos.x, game->player.pos.y);
	}
	// TODO figure this out
	if (keycode == A)
	{
		x += game->player.dir.x * MOVESPEED;
		y += game->player.dir.y * MOVESPEED;
		if (movement(game, x, y))
			return (0);
		game->player.pos.x += game->player.dir.x * MOVESPEED;
		game->player.pos.y += 0;
		movement(game, game->player.pos.x, game->player.pos.y);
	}
	if (keycode == D)
	{
		x -= game->player.dir.x * MOVESPEED;
		y -= game->player.dir.y * MOVESPEED;
		if (movement(game, x, y))
			return (0);
		game->player.pos.x -= game->player.dir.x * MOVESPEED;
		game->player.pos.y -= 0;
		movement(game, game->player.pos.x, game->player.pos.y);
	}

	// change direction with arrows
	if (keycode == RIGHT)
		rotate_player(game, ROTSPEED);
	if (keycode == LEFT)
		rotate_player(game, -ROTSPEED);

	return (0);
}
