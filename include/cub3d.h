/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:28:23 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/26 06:56:26 by emalungo         ###   ########.fr       */
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
void		clean_game(t_game *game, int mod);
int			check_extension(const char *str);
int			input_validation(int argc, char **argv);

// ./SRC/PARSE/PARSE_MAP.C
void		read_parse_file(t_game *game);
int			check_parse(t_game *game);
void		parse_path_texture(t_game *game, int i);
void		*ft_realloc(void *ptr, size_t new_size, size_t old_size);
void		handle_map_line(t_game *game, char *line, int *map_index);

#endif