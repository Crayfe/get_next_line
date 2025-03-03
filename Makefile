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

SRC_DIR = src
TEST_DIR = test

TEST_SRCS = $(TEST_DIR)/test_get_next_line.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

LIB_NAME = $(SRC_DIR)/get_next_line.a
NAME = test_get_next_line

all: $(NAME)

$(NAME): $(TEST_OBJS) $(LIB_NAME)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_NAME):
	@echo "Compiling GNL..."
	$(MAKE) -C $(SRC_DIR)

clean:
	rm -f $(TEST_OBJS)
	$(MAKE) clean -C $(SRC_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(SRC_DIR)

re: fclean all

.PHONY: all clean fclean re
