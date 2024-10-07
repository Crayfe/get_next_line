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

int	main(void){

	int	fd;
	char	*line;

	fd = open("file_test", 0);
	if (fd > 0)
	{
		line = get_next_line(fd);
		printf("Line: %s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
