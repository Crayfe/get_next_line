CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = get_next_line.c get_next_line_utils.c test_get_next_line.c
NAME = get_next_line
RM = rm -f

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)


fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean re
