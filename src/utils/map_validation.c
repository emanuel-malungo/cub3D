/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:23:00 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/26 07:09:14 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_extension(const char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4)
		return (0);
	if (str[len - 4] == '.' && str[len - 3] == 'c')
	{
		if (str[len - 2] == 'u' && str[len - 1] == 'b')
			return (1);
		return (0);
	}
	return (0);
}

int	check_map_shape(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->m.cols = 0;
	game->m.rows = 0;
	while (game->m.map[0][game->m.cols])
		game->m.cols++;
	while (game->m.map[game->m.rows])
		game->m.rows++;
	while (game->m.map[i])
	{
		j = 0;
		while (game->m.map[i][j])
			j++;
		if (game->m.cols != j)
			return (0);
		i++;
	}
	return (1);
}
