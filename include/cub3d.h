#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define WIDTH_SCREEN 800
# define HEIGHT_SCREEN 600

# define WALL_COLOR 0xD5D5D5

# define KEY_W 119
# define KEY_A 100
# define KEY_S 115
# define KEY_D 97
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_map
{
	int			fd;
	char		**map;
	char		**content;
	char		*path_north;
	char		*path_south;
	char		*path_to_west;
	char		*path_east;
	char		*floor_color;
	char		*ceiling_color;
}				t_map;

typedef struct s_player
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		cameraX;
}				t_player;

typedef struct s_ray
{
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	int			stepX;
	int			stepY;
	int			side;
	double		cameraX;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	int			color;
}				t_ray;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct cub3d
{
	t_map		m;
	t_player	p;
	void		*mlx_ptr;
	void		*mlx_win_ptr;
	t_img		img;
	t_ray		r;
}				t_cub3d;

// ./src/utils.c
t_cub3d			*init_cub3d(int argc, char **argv);
int				init_game(t_cub3d *cub3d);
int				read_file(t_cub3d *cub3d);
void			parse_content_file(t_cub3d *cub3d);

// ./src/utils/error_handling.c

// ./src/utils/player.c
void			get_player_position(t_cub3d *cub3d);

// ./src/ray_casting.c
int				ray_casting(t_cub3d *cub3d);

// ./src/draw.c
void			draw_background(t_cub3d *cub3d);
void			draw_vertical_line(t_cub3d *cub3d, int x, int drawStart,
					int drawEnd, int color);

#endif