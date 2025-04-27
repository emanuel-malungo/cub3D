/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:40:29 by emalungo          #+#    #+#             */
/*   Updated: 2025/04/06 15:24:11 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d *cub3d;

	if (!check_input_and_open_file(argc, argv[1], &cub3d))
		return (0);
	if (!read_file(cub3d))
		return (0);
	parse_content_file(cub3d);
	if (init_game(cub3d))
		return (0);
	free(cub3d);
	return (0);
}