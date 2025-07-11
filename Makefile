CC = cc
NAME = cub3d
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iinclude -Ilibft -Imlx

MLXDIR = mlx
SRCDIR = src
INCDIR = include
LIBFTDIR = libft

SRCS = $(SRCDIR)/cub3d.c \
       $(SRCDIR)/parse.c \
	   $(SRCDIR)/draw.c \
	   $(SRCDIR)/move.c \
       $(SRCDIR)/utils.c \
	   $(SRCDIR)/player.c \
	   $(SRCDIR)/texture.c \
	   $(SRCDIR)/ray_casting.c \
	   $(SRCDIR)/validate_map.c \
       $(SRCDIR)/error_handling.c \
       $(SRCDIR)/validate_colors.c \
       $(SRCDIR)/validate_texture.c \

OBJS = $(SRCS:.c=.o)
LIBFT = $(LIBFTDIR)/libft.a
MLX = $(MLXDIR)/libmlx.a
MLXFLAGS = -L$(MLXDIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLXFLAGS) -L$(LIBFTDIR) -lft

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(MLX):
	$(MAKE) -C $(MLXDIR)

%.o: %.c $(INCDIR)/so_long.h $(LIBFTDIR)/libft.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFTDIR)
	$(MAKE) clean -C $(MLXDIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean $(NAME)
