/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:31:46 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/26 02:36:34 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (!input_validation(argc, argv))
		return (0);
	game = init_struct_game();
	game->m.fd = open(argv[1], O_RDONLY);
	if (game->m.fd == -1)
	{
		free(game);
		ft_putstr_fd("Error: Cannot open map file.\n", 2);
		exit(EXIT_FAILURE);
	}
	read_parse_file(game);
	printf("North Texture Path: %s\n", game->m.path_north);
	printf("South Texture Path: %s\n", game->m.path_south);
	printf("West Texture Path: %s\n", game->m.path_to_west);
	printf("East Texture Path: %s\n", game->m.path_east);
	printf("Floor Color: %s\n", game->m.floor_color);
	printf("Ceiling Color: %s\n", game->m.ceiling_color);
    // int i = 0;
    // while (game->m.map[i])
    // {
    //     printf("%s\n", game->m.map[i]);
    //     i++;
    // }
	close(game->m.fd);
	return (1);
}
