/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 09:16:44 by mhirvasm          #+#    #+#             */
/*   Updated: 2025/12/18 12:55:35 by mhirvasm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int parse_and_validate_rgb(t_game *game)
{
	int red;
	int green;
	int blue;
	int color;
	int	i;
	
	color = -1;
	i = 0;
	while(game->map.textures[i])
	{
		if (game->map.textures[i][0] == 'C') // go parse the values  from here. 
		i++;
	}
	//get the color values here 
	if (red = ft_atoi() == 1)
		return(-1);
	if (green = ft_atoi() == 1)
		return (-1);
	if (blue = ft_atoi() == 1)
		return (-1);
	color = encode_rgb(red, green, blue);
	return (color);
}

//encode rgb vlues into 1 value that we can use in ceiling and floor 
int encode_rgb(int r,  int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}