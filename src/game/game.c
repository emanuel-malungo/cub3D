/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:46:16 by emalungo          #+#    #+#             */
/*   Updated: 2025/02/20 10:56:13 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	init_game(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
	{
		ft_putstr_fd("Error:\nFailed to initialize MiniLibX.\n", 2);
		clean_game(game, 1);
	}
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	if (!game->mlx.win_ptr)
	{
		ft_putstr_fd("Error: Failed to create window.\n", 2);
		clean_game(game, 1);
	}
    mlx_loop(game->mlx.mlx_ptr);
	return (0);
}
