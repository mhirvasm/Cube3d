#include "cub3d.h"

//pixel_put function
//writes pixel straightly to the memoryaddress  (fast)
void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->data + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

//draw the blocks (rectangles)
void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < BLOCK) // -1 so we have the "grid effect" and the blocks dont melt to each  other.
	{
		j = 0;
		while (j < BLOCK)
		{
			my_mlx_pixel_put(game, x * BLOCK + i, y * BLOCK + j, color); //x*block and y*block transforms map coordinates into pixel coordinates
			j++;
		}
		i++;
	}
}

//draw the 2d map
void	draw_2d_map(t_game *game)
{
	/*we need to loop over the grid, and if the current location == 1 (there is a wall)
	--> walls are for example white squares, and empty places == 0 are black squares for example.
	*/

	int	y;
	int	x;

	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == '1')
				draw_square(game, x, y, WHITE); // White walls
			else
				draw_square(game, x, y, BLACK); // Black floor
			x++;
		}
		y++;
	}
}

//draw the player
void	draw_player(t_game *game)
{
	// PRecise location as in pixels
	// (pos.x * BLOCK)
	int	px;
	int	py;
	int	size;
	int x;
	int y;

	px = (int)(game->player.pos.x * BLOCK);
	py = (int)(game->player.pos.y * BLOCK);
	size = 4; // player size
	y = -size; //-4 < 4
    while (y < size)
    {
        x = -size;
        while (x < size)
        {
            my_mlx_pixel_put(game, px + x, py + y, 0xFF0000);
			x++;
        }
        y++;
    }
}



static void draw_line(t_game *game, t_vector start, t_vector end, int color)
{
	double	delta_x;
	double	delta_y;
	double	pixel_x;
	double	pixel_y;
	int		pixels;

	delta_x = end.x - start.x;
	delta_y = end.y - start.y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = start.x;
	pixel_y = start.y;
	while (pixels)
	{
		my_mlx_pixel_put(game, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		pixels--;
	}
}

void draw_player_dir(t_game *game)
{
	t_vector	start;
	t_vector	end;


	start.x = game->player.pos.x * BLOCK;
	start.y = game->player.pos.y * BLOCK;

	end.x = start.x + (game->player.dir.x * 30);
	end.y = start.y + (game->player.dir.y * 30);

	draw_line(game, start, end, 0xFFFF00);
}

//render the frame (put image to window)
int	render_frame(t_game *game)
{
	draw_2d_map(game);
	raycast(game);
	draw_player(game);
	draw_player_dir(game);
	move_player(game);
	//draw  map
	//draw player
	//draw the image to window
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
