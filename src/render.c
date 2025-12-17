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
void	draw_square(t_game *game, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1) // -1 so we have the "grid effect" and the blocks dont melt to each  other.
	{
		j = 0;
		while (j < size - 1)
		{
			my_mlx_pixel_put(game, x * size + i, y * size + j, color); //x*block and y*block transforms map coordinates into pixel coordinates
			j++;
		}
		i++;
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
	if (pixels == 0)
		return ;
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

static void draw_player_dir(t_game *game, int tile_size)
{
	t_vector	start;
	t_vector	end;


	start.x = game->player.pos.x * tile_size;
	start.y = game->player.pos.y * tile_size;

	end.x = start.x + (game->player.dir.x * 30);
	end.y = start.y + (game->player.dir.y * 30);

	draw_line(game, start, end, 0xFFFF00);
}

//draw the player
void draw_player(t_game *game, int tile_size)
{
    int px = (int)(game->player.pos.x * tile_size); // Multiply with dynamic size
    int py = (int)(game->player.pos.y * tile_size);
    int size = tile_size / 3; // PLayer size related to tilesize
    if (size < 2) size = 2;

    int y = -size;
    while (y < size)
    {
        int x = -size;
        while (x < size)
        {
            my_mlx_pixel_put(game, px + x, py + y, 0xFF0000);
            x++;
        }
        y++;
    }
}

//drawing rays to maps
static	void draw_fov(t_game *game, int tile_size)
{
    int         x;
    t_ray       ray;
    t_vector    start;
    t_vector    end;

    
    x = 0;
    while (x < WIDTH)
    {

        init_ray(&ray, &game->player, x);


        perform_dda(game, &ray);


        start.x = game->player.pos.x * tile_size;
        start.y = game->player.pos.y * tile_size;

       
        end.x = ray.map.x * tile_size + (tile_size / 2);
        end.y = ray.map.y * tile_size + (tile_size / 2);


        draw_line(game, start, end, 0x00FF00);
		//lets do not draw all lines
        x += 50; 
    }
}

// src/render.c

static void draw_minimap_square(t_game *game, int x, int y, int color)
{
    int i;
    int j;

    // x and y tile coordinates transformed into pixels 
    int pixel_x = MM_OFFSET_X + (x * MM_TILE);
    int pixel_y = MM_OFFSET_Y + (y * MM_TILE);

    i = 0;
    while (i < MM_TILE)
    {
        j = 0;
        while (j < MM_TILE)
        {
            my_mlx_pixel_put(game, pixel_x + j, pixel_y + i, color);
            j++;
        }
        i++;
    }
}

static void draw_minimap(t_game *game)
{
    int y;
    int x;
    int map_y;
    int map_x;

    // Loop through minimap grid
    y = -MM_VIEW_DIST;
    while (y <= MM_VIEW_DIST)
    {
        x = -MM_VIEW_DIST;
        while (x <= MM_VIEW_DIST)
        {
            // calculate coordinates on the map
            map_y = (int)game->player.pos.y + y;
            map_x = (int)game->player.pos.x + x;

            // Check if its "inside" of the map
            if (map_y >= 0 && map_y < game->map.height &&
                map_x >= 0 && map_x < (int)ft_strlen(game->map.grid[map_y]))
            {
                // On map --> Check if its wall or floor
                if (game->map.grid[map_y][map_x] == '1')
                    draw_minimap_square(game, x + MM_VIEW_DIST, y + MM_VIEW_DIST, 0xFFFFFF); // Seinä
                else if (game->map.grid[map_y][map_x] != ' ') // Vältetään tyhjiä kohtia
                    draw_minimap_square(game, x + MM_VIEW_DIST, y + MM_VIEW_DIST, 0x000000); // Lattia
                else
                     draw_minimap_square(game, x + MM_VIEW_DIST, y + MM_VIEW_DIST, 0x222222); // Tyhjyys
            }
            x++;
        }
        y++;
    }

    // We draw the player on the middle of the map
    int center_x = MM_OFFSET_X + (MM_VIEW_DIST * MM_TILE) + (MM_TILE / 2);
    int center_y = MM_OFFSET_Y + (MM_VIEW_DIST * MM_TILE) + (MM_TILE / 2);
    
    // Here we draw the little player rectangle
 	int i = 0;
    while (i < 4)
    {
        int j = 0;
        while (j < 4)
        {
            my_mlx_pixel_put(game, center_x + j, center_y + i, RED);
            j++;
        }
        i++;
    }
}

//draw the 2d map
void draw_2d_map(t_game *game)
{
    int tile_size;
    int scale_w = WIDTH / game->map.width;
    int scale_h = HEIGHT / game->map.height;

    // choose the smaller scale, so the map can fit the screen
	if (scale_w < scale_h)
        tile_size = scale_w;
    else
	{
        tile_size = scale_h;
	}
	
	if (tile_size < 1)
		tile_size = 1;
	
    // draw using the tilesize
    int y = 0;
    while (game->map.grid[y])
    {
        int x = 0;
        while (game->map.grid[y][x])
        {
            if (game->map.grid[y][x] == '1')
                draw_square(game, x, y, tile_size, WHITE);
            else if (game->map.grid[y][x] != ' ')
                draw_square(game, x, y, tile_size, BLACK);
            x++;
        }
        y++;
    }
    draw_fov(game, tile_size);
    draw_player(game, tile_size);
    draw_player_dir(game, tile_size);
}

//render the frame (put image to window)
int	render_frame(t_game *game)
{
	move_player(game);
	if (DEBUG == 0) //DEBUG MACRO in the .h file!
	{
	raycast(game);
	draw_minimap(game);
	}
	if (DEBUG  == 1)
	{
		draw_2d_map(game);
	}
	//draw  map
	//draw player
	//draw the image to window
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

