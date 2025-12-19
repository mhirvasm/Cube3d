/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:05:51 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/12/19 09:46:47 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_colors(t_game *game, char **colors, int fd)
{
	int		i;
	int		j;
	int		l;
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
				l = 0;
				while (colors[i][j])
					line[l++] = colors[i][j++];
				line[l] = '\0';
				free(colors[i]);
				colors[i] = ft_strdup(line);
				free(line);
				break ;
			}
			j++;
		}
	}
}

static void	ft_free(char **array)
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
// we split the string using spaces as a delimiter and then replace the commas with a null terminator
// once we have only the numbers, we plug each string into atoi using indexes of the 2darray and return the color
int	parse_and_validate_rgb(t_game *game, char *texture)
{
	char	**rgb;
	int		color;
	int		i;
	int		j;

	i = 0;
	color = -1;
	rgb = ft_split(texture, ' ');
	if (!rgb)
		error_and_exit("Error. ft_split failure", game);
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (rgb[i][j] == ',')
				rgb[i][j] = '\0';
			j++;
		}
		i++;
	}
	if (ft_atoi(rgb[0]) == 1)
		return(-1);
	if (ft_atoi(rgb[1]) == 1)
		return (-1);
	if (ft_atoi(rgb[2]) == 1)
		return (-1);
	color = encode_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	ft_free(rgb);
	return (color);
}
 
//encode rgb vlues into 1 value that we can use in ceiling and floor
int	encode_rgb(int r,  int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
