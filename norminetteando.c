/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayuso-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:28:45 by cayuso-f          #+#    #+#             */
/*   Updated: 2024/10/04 14:08:27 by cayuso-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>

static char	*handle_nl_buffer(char *nl_buffer, char *next_line)
{
	char	*buffer_free;

	if (!nl_buffer)
	{
		nl_buffer = (char *)malloc(1);
		if (!nl_buffer)
			return (0);
		*nl_buffer = 0;
	}
	else
	{
		if (ft_strchr(nl_buffer, '\n'))
		{
			next_line = ft_substr(nl_buffer, 0, ft_strlen(nl_buffer, '\n') + 1);
			buffer_free = nl_buffer;
			nl_buffer = ft_substr(buffer_free, ft_strlen(nl_buffer, '\n')
					+ 1, ft_strlen(nl_buffer, 0));
			free(buffer_free);
			return (nl_buffer);
		}
	}
	return (nl_buffer);
}

static char	*read_nl(int fd, char *rd_buffer, char *nl_buffer, char *buffer_free)
{
	int			num_char_read;
	char		*next_line;

	rd_buffer = ft_memset(rd_buffer, 0, BUFFER_SIZE + 1);
	num_char_read = read(fd, rd_buffer, BUFFER_SIZE);
	if (num_char_read <= 0)
	{
		if (nl_buffer && ft_strlen(nl_buffer, 0) > 0)
		{
			next_line = ft_strjoin(nl_buffer, "\n");
			free(nl_buffer);
			nl_buffer = 0;
			return (next_line);
		}
		free(nl_buffer);
		return (0);
	}
	while (num_char_read == BUFFER_SIZE && !ft_strchr(rd_buffer, '\n'))
	{
		buffer_free = nl_buffer;
		nl_buffer = ft_strjoin(nl_buffer, rd_buffer);
		free(buffer_free);
		rd_buffer = ft_memset(rd_buffer, 0, BUFFER_SIZE + 1);
		num_char_read = read(fd, rd_buffer, BUFFER_SIZE);
	}
	buffer_free = ft_substr(rd_buffer, 0, ft_strlen(rd_buffer, '\n') + 1);
	next_line = ft_strjoin(nl_buffer, buffer_free);
	free(buffer_free);
	free(nl_buffer);
	nl_buffer = ft_substr(rd_buffer, ft_strlen(rd_buffer, '\n')
			+ 1, ft_strlen(rd_buffer, 0));
	free(rd_buffer);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*nl_buffer;
	char		*rd_buffer;
	char		*buffer_free;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	next_line = 0;
	nl_buffer = handle_nl_buffer(nl_buffer, next_line);
	if (!nl_buffer)
		return (0);
	if (next_line)
		return (next_line);
	rd_buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!rd_buffer)
		return (0);
	buffer_free = 0;
	next_line = read_nl(fd, rd_buffer, nl_buffer, buffer_free);
	return (next_line);
}
