# FILES
NAME	= get_next_line

# COMPILATION
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -Ofast -fno-builtin
LDFLAGS	= -L./libft -lft

$(NAME).o: $(NAME).c $(NAME).h
	make -C libft
	$(CC) $(CFLAGS) -c $< -o $@ -I./libft

all: $(NAME).o

clean:
	rm -rf $(NAME).o

fclean: clean

re: fclean all

%.out: %.c $(NAME).o $(NAME).h
	$(CC) $(CFLAGS) $< -o $@ -I. -I./libft $(LDFLAGS) $(NAME).o

.PHONY: all clean fclean re
