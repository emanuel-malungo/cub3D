/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 01:49:03 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/26 07:03:27 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	clean_arr(t_game *game)
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

void	clean_game(t_game *game, int mod)
{
	free(game->m.path_north);
	free(game->m.path_south);
	free(game->m.path_to_west);
	free(game->m.path_east);
	free(game->m.floor_color);
	free(game->m.ceiling_color);
	clean_arr(game);
	if (game->m.fd != -1)
		close(game->m.fd);
	if (mod == 1)
	{
		free(game);
		exit(1);
	}
}

static int	check_texture_parse(t_game *game)
{
	if (!game->m.path_north)
	{
		ft_putstr_fd("Error:\nMissing North texture path (NO)\n", 2);
		return (0);
	}
	if (!game->m.path_south)
	{
		ft_putstr_fd("Error:\nMissing South texture path (SO)\n", 2);
		return (0);
	}
	if (!game->m.path_to_west)
	{
		ft_putstr_fd("Error:\nMissing West texture path (WE)\n", 2);
		return (0);
	}
	if (!game->m.path_east)
	{
		ft_putstr_fd("Error:\nMissing East texture path (EA)\n", 2);
		return (0);
	}
	return (1);
}

int	check_parse(t_game *game)
{
	if (!check_texture_parse(game))
		return (0);
	if (!game->m.floor_color)
	{
		ft_putstr_fd("Error:\nMissing floor color (F)\n", 2);
		return (0);
	}
	if (!game->m.ceiling_color)
	{
		ft_putstr_fd("Error:\nMissing ceiling color (C)\n", 2);
		return (0);
	}
	return (1);
}

void	handle_map_line(t_game *game, char *line, int *map_index)
{
	game->m.map = ft_realloc(game->m.map, (*map_index + 2) * sizeof(char *),
			(*map_index) * sizeof(char *));
	game->m.map[*map_index] = ft_strdup(line);
	(*map_index)++;
	game->m.map[*map_index] = NULL;
}
