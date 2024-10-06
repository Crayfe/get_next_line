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

char	*get_next_line(int fd)
{
	static 	*buffer_next_line;
	char	*buffer_to_free;
	char	*new_buffer;
	char	*next_line;
	int num_char_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	next_line = 0;
	new_buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!new_buffer)
		return (0);
	new_buffer = ft_memset(new_buffer, 0, BUFFER_SIZE + 1);
	num_char_read = read(fd, new_buffer, BUFFER_SIZE);
	while (num_char_read == BUFFER_SIZE && !ft_strchr(new_buffer, '\n'))
	{
		buffer_to_free	= buffer_next_line;
		buffer_next_line = ft_strjoin(buffer_to_free, new_buffer);
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
		next_line = ft_strjoin(buffer_next_line, new_buffer + ft_strchr(new_buffer, '\n'));
		free(buffer_next_line);
		buffer_next_line = ft_substr(new_buffer + ft_strchr(new_buffer, '\n'));
	}
	free(new_buffer);
	return (next_line);
}

