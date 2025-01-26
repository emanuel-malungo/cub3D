/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:18:51 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/26 13:40:43 by emalungo         ###   ########.fr       */
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

void	validate_unique_entries(t_game *game)
{
	int	i;

	i = -1;
	while (game->m.content[++i])
	{
		if (ft_strncmp(game->m.content[i], "NO ", 3) == 0)
			game->m.count_no++;
		else if (ft_strncmp(game->m.content[i], "SO ", 3) == 0)
			game->m.count_so++;
		else if (ft_strncmp(game->m.content[i], "WE ", 3) == 0)
			game->m.count_we++;
		else if (ft_strncmp(game->m.content[i], "EA ", 3) == 0)
			game->m.count_ea++;
		else if (ft_strncmp(game->m.content[i], "F ", 2) == 0)
			game->m.count_f++;
		else if (ft_strncmp(game->m.content[i], "C ", 2) == 0)
			game->m.count_c++;
	}
	if (game->m.count_no > 1 || game->m.count_so > 1 || game->m.count_we > 1
		|| game->m.count_ea > 1 || game->m.count_f > 1 || game->m.count_c > 1)
	{
		ft_putstr_fd("Error:\nDuplicate entries detected in the map file\n", 2);
		clean_game(game, 1);
	}
}