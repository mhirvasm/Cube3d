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
static void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < BLOCK - 1) // -1 so we have the "grid effect" and the blocks dont melt to each  other.
	{
		j = 0;
		while (j < BLOCK - 1)
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

//render the frame (put image to window)