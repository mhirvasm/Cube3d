/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:54:23 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/05/26 14:01:51 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_strdup(char *s)
{
	char	*dup;
	int		size;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	size = gnl_strlen(s, '\0');
	dup = malloc(sizeof(char) * (size) + 1);
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*gnl_remainder_extractor(char *s)
{
	char	*temp1;
	char	*temp2;

	temp1 = gnl_strchr(s, '\n');
	if (temp1 && *(temp1 + 1))
	{
		temp2 = gnl_strdup(temp1 + 1);
		if (!temp2)
			return (free(s), NULL);
	}
	else
		temp2 = NULL;
	free(s);
	return (temp2);
}

static char	*gnl_looper(int fd, char *buf, char *stash)
{
	ssize_t	bytesread;

	bytesread = 1;
	while (bytesread > 0 && !(gnl_strchr(stash, '\n')))
	{
		bytesread = read(fd, buf, (BUFFER_SIZE));
		if (bytesread < 0 || BUFFER_SIZE == 0)
			return (free(stash), NULL);
		buf[bytesread] = '\0';
		stash = gnl_strjoin(stash, buf);
		if (!stash)
			return (NULL);
	}
	if ((bytesread == 0) && (!stash || *stash == '\0'))
		return (free(stash), NULL);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE + 1];
	static char		*stash;
	char			*line;

	line = NULL;
	if (!stash)
	{
		stash = gnl_strdup("");
		if (!stash)
			return (NULL);
	}
	if (gnl_strchr(stash, '\n') == NULL)
		stash = gnl_looper(fd, buf, stash);
	line = gnl_strtruncate(stash);
	if (!line)
		return (free(stash), NULL);
	stash = gnl_remainder_extractor(stash);
	return (line);
}
