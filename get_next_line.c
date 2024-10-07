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

char	*get_next_line(int fd)
{
	static char	*buffer_next_line;
	char	*buffer_to_free;
	char	*new_buffer;
	char	*next_line;
	int	num_char_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		printf("FLAG ERROR FD, BUFFER_SIZE, READ < 0");
		return (0);
	}
	new_buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!new_buffer)
		return (0);
	if (!buffer_next_line)
	{
		printf("VOID BUFFER\n");
		buffer_next_line = (char *)malloc(1);
		if (!buffer_next_line)
			return (0);
		*buffer_next_line = 0;
	}
	else
	{
		printf("SOME IN BUFFER: %s\n", buffer_next_line);
		printf("strlen_buffer: %zu\n", ft_strlen(buffer_next_line, 0));
		if (ft_strchr(buffer_next_line, '\n'))
		{
			next_line = ft_substr(buffer_next_line, 0, ft_strlen(buffer_next_line, '\n') + 1);
			buffer_to_free = buffer_next_line;
			buffer_next_line = ft_substr(buffer_to_free, ft_strlen(buffer_next_line, '\n') + 1, ft_strlen(buffer_next_line, 0));
			free(buffer_to_free);
			
			return (next_line);
		}
	}
	next_line = 0;
	new_buffer = ft_memset(new_buffer, 0, BUFFER_SIZE + 1);
	num_char_read = read(fd, new_buffer, BUFFER_SIZE);
	printf("NUM CHAR READ: %i\n", num_char_read);
	if (num_char_read <= 0)
	{
		if(buffer_next_line && ft_strlen(buffer_next_line, 0) > 0)
		{
			next_line = ft_strjoin(buffer_next_line, "\n");
			free(buffer_next_line);
			buffer_next_line = 0;
			return (next_line);
		}
		free(buffer_next_line);
		return (0);
	}
	while (num_char_read == BUFFER_SIZE && !ft_strchr(new_buffer, '\n'))
	{
		buffer_to_free	= buffer_next_line;
		buffer_next_line = ft_strjoin(buffer_to_free, new_buffer);
		printf("buffer_next_line: %s\n", buffer_next_line);
		free(buffer_to_free);
		new_buffer = ft_memset(new_buffer, 0, BUFFER_SIZE + 1);
		num_char_read = read(fd, new_buffer, BUFFER_SIZE);
	}
	if (num_char_read < BUFFER_SIZE && !ft_strchr(new_buffer, '\n'))
	{
		buffer_to_free	= buffer_next_line;
		buffer_next_line = ft_strjoin(buffer_to_free, new_buffer);
		free(buffer_to_free);
		next_line = ft_strjoin(buffer_next_line, "\n");
		free(buffer_next_line);
	}
	else
	{
		printf("srtlen: %zu\n", ft_strlen(new_buffer, '\n'));
		buffer_to_free = ft_substr(new_buffer, 0, ft_strlen(new_buffer, '\n') + 1);
		next_line = ft_strjoin(buffer_next_line, buffer_to_free);
		free(buffer_to_free);
		printf("next_line: %s\n", next_line);
		free(buffer_next_line);
		buffer_next_line = ft_substr(new_buffer, ft_strlen(new_buffer, '\n') + 1, ft_strlen(new_buffer, 0));
		printf("buffer_next_line: %s\n", buffer_next_line);
	}
	free(new_buffer);
	return (next_line);
}
