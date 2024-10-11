/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayuso-f <cayuso-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:28:45 by cayuso-f          #+#    #+#             */
/*   Updated: 2024/10/09 18:46:47 by cayuso-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>

char	*read_buffer(char *buffer, char c)
{
	char		*next_line;
	size_t		pos;
	size_t		i;

	pos = ft_strlen(buffer, c);
	if (c == '\n')
		next_line = ft_substr(buffer, 0, pos + 1);
	else
		next_line = ft_substr(buffer, 0, pos);
	i = 0;
	if (ft_strlen(buffer + pos + 1, 0))
	{
		while (buffer[pos + i + 1])
		{
			buffer[i] = buffer[pos + i + 1];
			i++;
		}
		ft_memset(buffer + i, 0, BUFFER_SIZE + 1 - i);
	}
	else
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
	return (next_line);
}

char	*read_endcases(char *buffer, char *next_line, char *to_free)
{
	if (ft_strlen(buffer, 0))
	{
		if (ft_strchr(buffer, '\n'))
			to_free = read_buffer(buffer, '\n');
		else
			to_free = read_buffer(buffer, 0);
		next_line = ft_strjoin(next_line, to_free);
		free(to_free);
	}
	else if (!ft_strlen(next_line, 0))
	{
		free(next_line);
		next_line = 0;
	}
	return (next_line);
}

char	*read_line(char *buffer, int fd, char *to_free)
{
	char	*next_line;
	size_t	rd_chars;

	next_line = malloc(1);
	*next_line = 0;
	rd_chars = read(fd, buffer, BUFFER_SIZE);
	while (rd_chars == BUFFER_SIZE && !ft_strchr(buffer, '\n'))
	{
		next_line = ft_strjoin(next_line, buffer);
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
		rd_chars = read(fd, buffer, BUFFER_SIZE);
	}
	if (rd_chars < BUFFER_SIZE)
		next_line = read_endcases(buffer, next_line, to_free);
	else
	{
		to_free = read_buffer(buffer, '\n');
		next_line = ft_strjoin(next_line, to_free);
		free(to_free);
	}
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*next_line;
	char		*to_free;

	to_free = 0;
	next_line = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	if (ft_strlen(buffer, 0))
	{
		if (ft_strchr(buffer, '\n'))
			next_line = read_buffer(buffer, '\n');
		else
			next_line = read_buffer(buffer, 0);
	}
	if (next_line && ft_strchr(next_line, '\n'))
		return (next_line);
	else
		next_line = read_line(buffer, fd, to_free);
	return (next_line);
}
