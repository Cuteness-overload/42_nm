NAME =	libft.a

SRCS =	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strcmp.c \
		buf_utils.c \
		parser.c \
		printf.c \
		render_num_utils_b.c \
		render_num_utils.c \
		render_num.c \
		render_str_utils.c \
		render_str.c \
		render.c \
		utils.c


SDIRS =	./
IDIRS =	./

SFILES = $(addprefix $(SDIRS),$(SRCS))
BFILES = $(addprefix $(SDIRS),$(BONUS))
OSFILES = $(patsubst %.c,%.o,$(SFILES))
OBFILES = $(patsubst %.c,%.o,$(BFILES))

CC = cc
CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OSFILES)
	ar -rcs $(NAME) $^

bonus: $(NAME) $(OBFILES)
	ar -rcs $(NAME) $^

all: bonus

clean:
	rm -f $(OSFILES)
	rm -f $(OBFILES)

fclean: clean
	rm -f $(NAME)
	rm -f libft.so

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -I$(IDIRS) -c -o $@ $^

.PHONY: bonus all clean fclean re
