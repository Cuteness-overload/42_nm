CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
#PRINTF_DIR = $(LIBFT_DIR)/printf
LIBFT = $(LIBFT_DIR)/libft.a
#PRINTF = $(PRINTF_DIR)/libftprintf.a
SRCS = ft_nm.c \
	   utils.c \
	   sort.c \
	   symbols.c \
	   nm_64.c \
	   nm_32.c \
	   args.c

PATHS = $(addprefix srcs/, $(SRCS))
OBJS = $(PATHS:.c=.o)
NAME = ft_nm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re