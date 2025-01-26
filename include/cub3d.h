/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:28:23 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/26 02:11:35 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_map
{
	int		fd;
	char	**map;
	char	*buffer;
	char	*floor_color;
	char	*ceiling_color;
	char	**content;
	char	*path_north;
	char	*path_south;
	char	*path_to_west;
	char	*path_east;
}			t_map;

typedef struct s_game
{
	t_map	m;
}			t_game;

// ./SRC/UTILS/UTILS.C

t_game		*init_struct_game(void);
void		clean_struct_game(t_game *game);
int			input_validation(int argc, char **argv);
int			check_extension(const char *str);

// ./SRC/PARSE/PARSE_MAP.C
int			check_parse(t_game *game);
void		read_parse_file(t_game *game);
void		parse_path_texture(t_game *game, int i);

#endif