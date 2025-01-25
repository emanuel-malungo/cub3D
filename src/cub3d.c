/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:31:46 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/25 23:16:21 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
    t_game *game;

	if (!input_validation(argc, argv))
		return (0);
    game = init_struct_game();
    game->fd = open(argv[1], O_RDONLY);
    if (game->fd == -1)
    {
        free(game);
        ft_putstr_fd("Error: Cannot open map file.\n", 2);
        exit(EXIT_FAILURE);
    }
    printf("File opened successfully\n");
    close(game->fd);
    free(game);
	return (1);
}
