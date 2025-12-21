#include "cub3d.h"

void raycast(t_game *game)
{
	t_ray	ray;

	ft_bzero(&ray, sizeof(t_ray));

    int x = 0;

    while (x < WIDTH) 
    {
        //init ray for this position x 
        init_ray(&ray, &game->player, x);
        
        //calculate whhere the ray hits
        perform_dda(game, &ray);
		//fix values before draw
		calculate_wall_dist(&ray);
        //draw
		draw_walls(game, x, &ray);
        x++; //move to next vertical line
    }
}

// We need the ray starting position (its x,y position)
// Remember that we first need to find a spot from horizontal or vertical linepoint
// Init ray calculates this starting point, where we send the ray 

//In a nutshell we need 3 things: 
								// direction of the ray
								// Starting position of the ray
								// Start distance for the first vertical or horizontal line of the grid

void init_ray(t_ray *ray, t_player *player, int x)
{
    double camera_x;

    camera_x = 2 * x / (double)WIDTH - 1;

	//ray direction init
    ray->direction.x = player->dir.x + (player->plane.x * camera_x);
    ray->direction.y = player->dir.y + (player->plane.y * camera_x);

	//ray start pos init
    ray->map.x = (int)player->pos.x;
    ray->map.y = (int)player->pos.y;

    //length of one step
    if (ray->direction.x == 0)
        ray->delta_dist.x = 1e30; // ("infinity")
    else
        ray->delta_dist.x = fabs(1.0 / ray->direction.x);

    if (ray->direction.y == 0)
        ray->delta_dist.y = 1e30;
    else
        ray->delta_dist.y = fabs(1.0 / ray->direction.y);

    //calculating  step for  the first "grid line"

    // x axis
    if (ray->direction.x < 0)
    {
        ray->step.x = -1; //-1 for left
        ray->side_dist.x = (player->pos.x - ray->map.x) * ray->delta_dist.x;
    }
    else
    {
        ray->step.x = 1; //1 for rright
        ray->side_dist.x = (ray->map.x + 1.0 - player->pos.x) * ray->delta_dist.x;
    }

    // y axis
    if (ray->direction.y < 0)
    {
        ray->step.y = -1; //-1 for up
        ray->side_dist.y = (player->pos.y - ray->map.y) * ray->delta_dist.y;
    }
    else
    {
        ray->step.y = 1; //1 for down
        ray->side_dist.y = (ray->map.y + 1.0 - player->pos.y) * ray->delta_dist.y;
    }
}

void	perform_dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;

	while (!!!hit)
	{
		//check which one wins, x or y axis
		if (ray->side_dist.x < ray->side_dist.y)
		{
			//x axis won

			// increase side_dist_x by adding delta_dist_x into it
			ray->side_dist.x += ray->delta_dist.x;
            
            // move map coordinate with step we intialized in init
            ray->map.x += ray->step.x;
            // mark that we hit "vertical wall"
			ray->side = 0;
		}
		//else sidedisty < sidesistx
		else
		{
			//y axis won

			// increase side_dist_y by adding delta_dist_y into it
			ray->side_dist.y += ray->delta_dist.y;
            
            // move map coordinate with step we intialized in init
            ray->map.y += ray->step.y;
            // mark that we hit "horizontal walll"
			ray->side = 1;
		}
		if (game->map.grid[ray->map.y][ray->map.x] == '1')
			hit = 1;
	}
	if (ray->side == 0)
	{
		if (game->player.dir.x == 1)
			game->map.color = EAST;
		else
			game->map.color = WEST;
	}
	else
	{
		if (game->player.dir.y == 1)
			game->map.color = NORTH;
		else
			game->map.color = SOUTH;
	}
}

//in the end of dda, we are "one step too far", so we want to fix the distance values by goin one step back
void calculate_wall_dist(t_ray *ray)
{
    
    if (ray->side == 0)
        ray->wall_dist = (ray->side_dist.x - ray->delta_dist.x);
    else
        ray->wall_dist = (ray->side_dist.y - ray->delta_dist.y);
    //calculate the height of the wall, the smaller the number, more far the wall is located
    ray->line_height = (int)(HEIGHT / ray->wall_dist);

    // calculate the start of the draw, and end of the draw
    ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;

	//if we are very close to the wall and the value would turnout to be minus value, we initialize the value to 0 coz we cant draw to -1 indexes
    if (ray->draw_start < 0)
        ray->draw_start = 0;

    ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
    if (ray->draw_end >= HEIGHT)
        ray->draw_end = HEIGHT - 1;
}

void draw_walls(t_game *game, int x, t_ray *ray)
{
    int y;

    y = 0;
    while (y < ray->draw_start)
    {
        my_mlx_pixel_put(game, x, y, game->ceiling_color);
        y++;
    }

    // this is only drawing a wall for now
//	y = ray->draw_start;
//	while (y < ray->draw_end)
	y = ray->draw_end;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(game, x, y, game->floor_color);
		y++;
	}
//	walls(game, x, ray);
}
