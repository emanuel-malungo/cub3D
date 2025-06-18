/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:30:04 by emalungo          #+#    #+#             */
/*   Updated: 2025/06/17 13:13:13 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
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
}			t_map;

typedef struct s_cub3d
{
	int		fd;
	t_map	m;
	char	**file_content;
}			t_cub3d;

// ./src/utils.c
int			check_extension(char *str);
t_cub3d		*init_cub3d(int argc, char **argv);

// ./src/parse.c
int			parse(t_cub3d *cub3d);

#endif