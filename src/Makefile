# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cayuso-f <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 16:58:10 by cayuso-f          #+#    #+#              #
#    Updated: 2024/10/02 15:56:17 by cayuso-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = get_next_line.a

SRC = get_next_line_utils.c get_next_line.c
OBJ = $(SRC:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJ) 
		ar rcs $(NAME) $(OBJ)

clean	:
		rm -f $(OBJ)

fclean	: 	clean
		rm -f $(NAME)

re	: 	fclean all

.DEFAULT_GOAL := all
.PHONY: all clean fclean re
