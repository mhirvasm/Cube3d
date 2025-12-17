/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:05:51 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/12/17 15:06:01 by vahdekiv         ###   ########.fr       */
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
