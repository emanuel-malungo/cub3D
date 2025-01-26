/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:18:51 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/26 08:01:15 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	input_validation(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error:\nUsage: ./cub3d <map_file>\n", 2);
		return (0);
	}
	if (!check_extension(argv[1]))
	{
		ft_putstr_fd("Error:\nInvalid file extension.\n", 2);
		return (0);
	}
	return (1);
}

void	map_validation(t_game *game)
{
	if (!check_map_shape(game))
	{
		ft_putstr_fd("Error:\nMap must be rectangular.\n", 2);
		clean_game(game, 1);
	}
	if (!check_wall_map(game))
	{
		ft_putstr_fd("Error:\nInvalid walls.\n", 2);
		clean_game(game, 1);
	}
	if (!check_valid_map_characters(game))
	{
		ft_putstr_fd("Error:\nInvalid elements found in the map.\n", 2);
		clean_game(game, 1);
	}
	if (!check_single_spawn_point(game))
	{
		ft_putstr_fd("Error:\nThere must be exactly one spawn point.\n", 2);
		clean_game(game, 1);
	}
}