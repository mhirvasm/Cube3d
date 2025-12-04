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
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		error_and_exit("Game closed", game);
	if (keycode == W)
		game->player.key_up = true;
	if (keycode == S)
		game->player.key_down = true;
	if (keycode == A)
		game->player.key_left = true;
	if (keycode == D)
		game->player.key_right = true;
	if (keycode == RIGHT)
		game->player.right_rotate = true;
	if (keycode == LEFT)
		game->player.left_rotate = true;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key_up = false;
	if (keycode == S)
		game->player.key_down = false;
	if (keycode == A)
		game->player.key_left = false;
	if (keycode == D)
		game->player.key_right = false;
	if (keycode == RIGHT)
		game->player.right_rotate = false;
	if (keycode == LEFT)
		game->player.left_rotate = false;
	return (0);
}

void	move_player(t_game *game)
{
	if (game->player.key_up)
	{
		if (movement(game, game->player.pos.x, game->player.pos.y - 0.1))
			return ;
		game->player.pos.y -= MOVESPEED;
	}
	if (game->player.key_down)
	{
		if (movement(game, game->player.pos.x, game->player.pos.y + 0.1))
			return ;
		game->player.pos.y += MOVESPEED;
	}
	if (game->player.key_left)
	{
		if (movement(game, game->player.pos.x - 0.1, game->player.pos.y))
			return ;
		game->player.pos.x -= MOVESPEED;
	}
	if (game->player.key_right)
	{
		if (movement(game, game->player.pos.x + 0.1, game->player.pos.y))
			return ;
		game->player.pos.x += MOVESPEED;
	}
	// rotation does not work yet
	if (game->player.right_rotate)
		rotate_player(game, ROTSPEED);
	if (game->player.left_rotate)
		rotate_player(game, -ROTSPEED);
}
