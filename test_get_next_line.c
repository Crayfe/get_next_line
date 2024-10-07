/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayuso-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:31:43 by cayuso-f          #+#    #+#             */
/*   Updated: 2024/10/04 12:59:54 by cayuso-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 150


/*	AUXILIAR FUNCTIONS	*/
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*aux_s;

	i = 0;
	aux_s = (unsigned char *)s;
	while (i < n)
		aux_s[i++] = c;
	return (s);
}
size_t	ft_strlen(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (0);
}


size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src, 0));
	i = 0;
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src, 0));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	k;

	i = ft_strlen(dst, 0);
	k = ft_strlen(src, 0);
	if ((!dst || !src) && size == 0)
		return (0);
	if (size < i)
		return (size + k);
	ft_strlcpy(dst + i, src, size - i);
	return (i + k);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	aux_len;

	if (!s)
		return (0);
	if ((size_t) start > ft_strlen(s, 0))
	{
		sub = (char *)malloc(1);
		*sub = 0;
		return (sub);
	}
	if (len > ft_strlen(s, 0) - (size_t) start)
		aux_len = ft_strlen(s, 0) - (size_t) start;
	else
		aux_len = len;
	sub = (char *)malloc(aux_len + 1);
	if (!sub)
		return (0);
	ft_strlcpy(sub, s + start, aux_len + 1);
	return (sub);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1, 0);
	len2 = ft_strlen(s2, 0);
	join = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!join)
		return (0);
	ft_strlcpy(join, s1, len1 + 1);
	ft_strlcat(join, s2, len1 + len2 + 1);
	return (join);
}

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

int	main(void){

	int	fd;
	char	*line;
	int	i;

	i = 0;
	fd = open("file_test", 0);
	if (fd > 0)
	{
		while (i < 23)
		{
			line = get_next_line(fd);
			printf("Line: %s\n", line);
			free(line);
			i++;
		}
	}
	close(fd);
	return (0);
}
