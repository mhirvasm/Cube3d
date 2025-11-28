/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:54:52 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/05/26 14:00:07 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char	*s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	*gnl_strtruncate(char *s)
{
	char	*dup;
	int		size;
	int		i;
	char	*string;

	if (!s)
		return (NULL);
	i = 0;
	if (gnl_strchr(s, '\n') == NULL)
		size = gnl_strlen(s, '\0');
	else
		size = gnl_strlen(s, '\n');
	string = gnl_strchr(s, '\n');
	if (string)
		size++;
	dup = malloc(sizeof(char) * (size + 1));
	if (!dup)
		return (NULL);
	while (s[i] && i < size)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*gnl_strcpy(char *dest, char *src, size_t n)
{
	size_t				i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*newstr;

	if (!s1)
		return (gnl_strtruncate(s2));
	if (s1 && s2)
	{
		len1 = gnl_strlen(s1, '\0');
		len2 = gnl_strlen(s2, '\0');
		newstr = malloc(len1 + len2 + 1);
		if (!newstr)
			return (free(s1), NULL);
		gnl_strcpy(newstr, s1, len1);
		gnl_strcpy(newstr + len1, s2, len2);
		newstr[len1 + len2] = '\0';
		free(s1);
		return (newstr);
	}
	free(s1);
	return (NULL);
}

char	*gnl_strchr(char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
		{
			return ((char *) s);
		}
		s++;
	}
	if (c == '\0')
		return ((char *) s);
	return (NULL);
}
