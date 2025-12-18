/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 09:16:44 by mhirvasm          #+#    #+#             */
/*   Updated: 2025/12/18 12:44:23 by mhirvasm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int parse_and_validate_rgb(t_game *game)
{
	int red;
	int green;
	int blue;
	int	i;
	
	i = 0;
	while(game->map.textures[i])
	{
		if (game->map.textures[i][0] == 'C')
		i++;
	}
	
	if (red = ft_atoi() == 1)
		return(1);
	if (green = ft_atoi() == 1)
		return (1);
	if (blue = ft_atoi() == 1)
		return (1);
	return (0);
}

//encode rgb vlues into 1 value that we can use in ceiling and floor 
int encode_rgb(int r,  int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}