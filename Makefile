CC := cc
NAME := cub3D

CFLAGS := -Iinclude -Ilibft -Wall -Wextra -Werror -O2
LDFLAGS := -Lmlx_Linux -lmlx_Linux -lXext -lX11 -lm

SRC := src/exit/free_elements.c src/movements/movements.c src/movements/movementsutils2.c \
		src/movements/movementsutils.c src/parsing/charsinmap.c src/parsing/gnl.c src/parsing/main.c \
		src/parsing/fixe_lile.c src/parsing/split2.c src/parsing/splits.c src/parsing/utilsparsing2.c \
		src/parsing/utilsparsing.c src/ray-casting/caster.c src/ray-casting/draw2Dmap.c src/ray-casting/draw2Dmaputils.c \
		src/ray-casting/mlx_utils.c src/ray-casting/mlx.c src/ray-casting/player.c src/ray-casting/raycasting.c src/textures/texture.c src/textures/texture_utils.c \
		src/vec2/vec2.c src/vec2/vec2utils.c src/vec3/vec3.c src/movements/mouse.c \
		libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa.c libft/ft_lstadd_front_bonus.c libft/ft_lstnew_bonus.c libft/ft_lstsize_bonus.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_striteri.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re