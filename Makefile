# FILES
BASE	= get_next_line
NAME	= $(BASE).o
INC		= $(BASE).h
SRC		= $(BASE).c

# COMPILATION
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -Ofast -fno-builtin -g
LDFLAGS	= -I./libft -L./libft -lft

all: $(NAME)

$(NAME): $(SRC) $(INC)
	make -C libft
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

%.out: %.c $(INC) $(NAME)
	$(CC) $(CFLAGS) $< -o $@ $(NAME) -I. $(LDFLAGS)

.PHONY: all clean fclean re
