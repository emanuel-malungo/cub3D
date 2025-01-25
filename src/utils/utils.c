/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 23:00:32 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/25 23:11:55 by emalungo         ###   ########.fr       */
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
