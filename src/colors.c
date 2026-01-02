/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirvasm <mhirvasm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:05:51 by vahdekiv          #+#    #+#             */
/*   Updated: 2026/01/02 11:20:13 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_colors(t_game *game, char **colors, int fd)
{
	int		i;
	int		j;
	char	*line;

	i = 3;
	while (colors[++i])
	{
		j = 0;
		while (colors[i][j])
		{
			if (colors[i][j] != 'F' && colors[i][j] != 'C')
			{
				line = malloc((ft_strlen(colors[i]) - j) * sizeof(char));
				if (!line)
				{
					close(fd);
					error_and_exit("Error. Malloc failure.", game);
				}
				texture_helper(colors, i, j, line);
				break ;
			}
			j++;
		}
	}
}

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i])
		{
			free(array[i]);
			array[i] = NULL;
		}
		i++;
	}
	if (array)
		free(array);
}

// we split the string using spaces as a delimiter and then replace
//	the commas with a null terminator
// once we have only the numbers, we plug each string into atoi using
//indexes of the 2darray and return the color
int	parse_and_validate_rgb(t_game *game, char *texture)
{
	char	**rgb;
	int		i;
	int		j;

	i = 0;
	game->color = -1;
	rgb = ft_split(texture, ' ');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_free(rgb);
		error_and_exit("Error. ft_split failure", game);
	}
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (rgb[i][j] == ',' || rgb[i][j] == '\n')
				rgb[i][j] = '\0';
			j++;
		}
		i++;
	}
	game->color = rgb_helper(game, rgb);
	return (game->color);
}

//encode rgb vlues into 1 value that we can use in ceiling and floor
int	encode_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
