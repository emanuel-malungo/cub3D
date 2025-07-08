/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:30:04 by emalungo          #+#    #+#             */
/*   Updated: 2025/07/08 13:23:57 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH_SCREEN 800
# define HEIGHT_SCREEN 600

# define KEY_W 119
# define KEY_A 100
# define KEY_S 115
# define KEY_D 97
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_texture
{
	void		*img_n;
	void		*img_s;
	void		*img_e;
	void		*img_w;
	char		*path_north;
	char		*path_south;
	char		*path_west;
	char		*path_east;
	t_img		texture_north;
	t_img		texture_south;
	t_img		texture_west;
	t_img		texture_east;
}				t_texture;

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

typedef struct s_map
{
	char		**map_content;
	char		*floor_color;
	char		*ceiling_color;
	int			width;
	int			heigth;
}				t_map;

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

typedef struct s_cub3d
{
	int			fd;
	t_map		m;
	t_texture	t;
	t_player	p;
	t_img		i;
	void		*mlx_ptr;
	void		*mlx_win_ptr;
	char		**file_content;
}				t_cub3d;

// ./src/utils.c
void			ft_free_matrix(char **matrix);
void			cleanup_cub3d(t_cub3d *cub3d);
t_cub3d			*init_cub3d(int argc, char **argv);

// ./src/parse.c
int				parse(t_cub3d *cub3d);

// ./src/error_handling.c
int				check_extension(char *str);
int				check_required_identifiers(t_cub3d *cub3d);

// ./src/validate_texture.c
int				validate_texture_paths(t_cub3d *cub3d);

// ./src/validate_colors.c
void			validate_colors(t_cub3d *cub3d);

// ./src/validate_map.c
int				check_map_wall(t_cub3d *cub3d);
int				check_elements_map(char **map);

// ./src/texture.c
int				lead_texture(t_cub3d *cub3d);

// ./src/player.c
void			get_player_position(t_cub3d *cub3d);

// ./src/draw.c
void			draw_background(t_cub3d *cub3d);
int				get_pixel_color(t_img *texture, int x, int y);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);

// ./src/ray_casting.c
int				ray_casting(t_cub3d *cub3d);

// ./src/move.c
int handle_key_press(int keycode, t_cub3d *cub3d);

#endif