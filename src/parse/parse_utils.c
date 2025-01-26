/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 01:49:03 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/26 02:30:38 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_texture_parse(t_game *game)
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
