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
	char	*next_line;
	int		pos;
	int		i;

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

char	*read_endcases(char *buffer, char *next_line)
{
	if (!ft_strlen(buffer, 0))
	{
		if (*next_line)
		{
			next_line = ft_strjoin(next_line, "\n");
			return (next_line);
		}
		else
			free(next_line);
		return (0);
	}
	else
	{
		if (!ft_strchr(buffer, '\n'))
		{
			next_line = ft_strjoin(next_line, buffer);
			next_line = ft_strjoin(next_line, "\n");
			ft_memset(buffer, 0, BUFFER_SIZE + 1);
		}
		else
			next_line = ft_strjoin(next_line, read_buffer(buffer, '\n'));
	}
	return (next_line);
}

char	*read_line(char *buffer, char *next_line, int fd, int rd_chars)
{
	rd_chars = read(fd, buffer, BUFFER_SIZE);
	while (rd_chars == BUFFER_SIZE && !ft_strchr(buffer, '\n'))
	{
		next_line = ft_strjoin(next_line, buffer);
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
		rd_chars = read(fd, buffer, BUFFER_SIZE);
	}
	if (rd_chars < BUFFER_SIZE)
	{
		next_line = read_endcases(buffer, next_line);
	}
	else
		next_line = ft_strjoin(next_line, read_buffer(buffer, '\n'));
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*next_line;
	int			rd_chars;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	next_line = malloc(1);
	*next_line = 0;
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
	{
		rd_chars = 0;
		next_line = read_line(buffer, next_line, fd, rd_chars);
	}
	return (next_line);
}
