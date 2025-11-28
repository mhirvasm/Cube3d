/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:01:10 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/08/13 11:57:52 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*gnl_strtruncate(char *s);
char	*gnl_strchr(char *s, char c);
char	*gnl_strcpy(char *dest, char *src, size_t n);
char	*gnl_strjoin(char *s1, char *s2);
int		gnl_strlen(char *s, char c);

#endif
