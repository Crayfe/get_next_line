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
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open("file_test", 0);
	if (fd > 0)
	{
		while (i < 29)
		{
			line = get_next_line(fd);
			if (!line)
			{
				printf("\033[0;32mEnd of file\n");
				close(fd);
				return (0);
			}
			printf("\033[0;32mLine: %s\n", line);
			free(line);
			i++;
		}
	}
	close(fd);
	return (0);
}
