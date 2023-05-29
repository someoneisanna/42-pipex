NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MAKE = make -C
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = mandatory/pipex.c mandatory/pipex_utils.c
S_OBJS = $(SRCS:.c=.o)

BONUS_SRCS = bonus/pipex_bonus.c bonus/pipex_utils_bonus.c
B_OBJS = $(BONUS_SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(S_OBJS)
	$(MAKE) $(LIBFT_DIR) all
	$(CC) $(CFLAGS) $(S_OBJS) $(LIBFT) -o $(NAME) -I.

bonus: $(B_OBJS)
	$(MAKE) $(LIBFT_DIR) all
	$(CC) $(CFLAGS) $(B_OBJS) $(LIBFT) -o $(NAME) -I.

clean:
	$(MAKE) $(LIBFT_DIR) clean
	$(RM) $(S_OBJS)
	$(RM) $(B_OBJS)

fclean: clean
	$(MAKE) $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all
