/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:30:04 by emalungo          #+#    #+#             */
/*   Updated: 2025/07/03 00:51:26 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_map
{
	char	**map_content;
	char	*path_north;
	char	*path_south;
	char	*path_west;
	char	*path_east;
	char	*floor_color;
	char	*ceiling_color;
	int		width;
	int		heigth;
}			t_map;

typedef struct s_cub3d
{
	int		fd;
	t_map	m;
	char	**file_content;
}			t_cub3d;

// ./src/utils.c
void		ft_free_matrix(char **matrix);
void		cleanup_cub3d(t_cub3d *cub3d);
t_cub3d		*init_cub3d(int argc, char **argv);

// ./src/parse.c
int			parse(t_cub3d *cub3d);

// ./src/error_handling.c
int			check_extension(char *str);
int			check_required_identifiers(t_cub3d *cub3d);

// ./src/validate_texture.c
int			validate_texture_paths(t_cub3d *cub3d);

// ./src/validate_colors.c
void		validate_colors(t_cub3d *cub3d);

// ./src/validate_map.c
int			check_map_wall(t_cub3d *cub3d);
int			check_elements_map(char **map);

#endif