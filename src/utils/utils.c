/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 23:00:32 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/26 02:07:01 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_game	*init_struct_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
	{
		ft_putstr_fd("Error: Memory allocation failed.\n", 2);
		return (NULL);
	}
	ft_memset(game, 0, sizeof(t_game));
	return (game);
}

void	clean_arry(t_game *game)
{
	int	i;

	if (game->m.map)
	{
		i = 0;
		while (game->m.map[i])
		{
			free(game->m.map[i]);
			i++;
		}
		free(game->m.map);
	}
	if (game->m.content)
	{
		i = 0;
		while (game->m.content[i])
		{
			free(game->m.content[i]);
			i++;
		}
		free(game->m.content);
	}
}

void	clean_struct_game(t_game *game)
{
	if (game->m.path_north)
		free(game->m.path_north);
	if (game->m.path_south)
		free(game->m.path_south);
	if (game->m.path_to_west)
		free(game->m.path_to_west);
	if (game->m.path_east)
		free(game->m.path_east);
	if (game->m.floor_color)
		free(game->m.floor_color);
	if (game->m.ceiling_color)
		free(game->m.ceiling_color);
	if (game->m.buffer)
		free(game->m.buffer);
}
