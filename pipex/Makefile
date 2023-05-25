NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar -rcs
MAKE = make -C
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = pipex.c pipex_utils.c

S_OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I.

$(NAME): $(S_OBJS)
	$(MAKE) $(LIBFT_DIR) all
	$(CC) $(CFLAGS) $(S_OBJS) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) $(LIBFT_DIR) clean
	$(RM) $(S_OBJS)

fclean: clean
	$(MAKE) $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all
