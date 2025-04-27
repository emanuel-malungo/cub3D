#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
#include <string.h>
#include <math.h>

# define WIDTH 800
# define HEIGHT 600

# define KEY_W 119
# define KEY_A 100
# define KEY_S 115
# define KEY_D 97
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

#define WALL_COLOR 0x4A4A4A    // Cinza escuro para paredes
#define FLOOR_COLOR 0xB3B3B3   // Cinza claro para chão
#define PLAYER_COLOR 0xFFD700   // Dourado para jogador
#define BACKGROUND_COLOR 0x1A1A1A // Preto escuro para fundo

typedef struct s_map
{
	int		fd;
	char	**map;
	char	**content;
	char	*path_north;
	char	*path_south;
	char	*path_to_west;
	char	*path_east;
	char	*floor_color;
	char	*ceiling_color;
}			t_map;

typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}			t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct cub3d
{
	t_map	m;
	t_player p;
	void	*mlx_ptr;
	void	*mlx_win_ptr;
	t_img	img;
}			t_cub3d;


// ./src/utils/utils.c
t_cub3d		*init_cub3d(void);
int			init_game(t_cub3d *cub3d);
int			read_file(t_cub3d *cub3d);
void		parse_content_file(t_cub3d *cub3d);

// ./src/utils/error_handling.c
int			check_input_and_open_file(char argc, char *file, t_cub3d **cub3d);

// ./src/utils/render.c
int	render_map(t_cub3d *cub3d);

#endif