NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iinclude -Ilibft -Imlx

SRCDIR = src
INCDIR = include
LIBFTDIR = libft
MLXDIR = mlx

SRCS = $(SRCDIR)/cub3d.c \
	   

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