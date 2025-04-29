/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:29:57 by emalungo          #+#    #+#             */
/*   Updated: 2025/04/29 09:51:56 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	cub3d = init_cub3d(argc, argv);
	if (!cub3d)
		return (0);
	cub3d->m.fd = open(argv[1], O_RDONLY);
	if (cub3d->m.fd < 0)
	{
		ft_putstr_fd("Error\nCould not open file\n", 2);
		return (0);
	}
	if (!read_file(cub3d))
	{
		close(cub3d->m.fd);
		return (0);
	}
	parse_content_file(cub3d);
	if (!init_game(cub3d))
	{
		close(cub3d->m.fd);
		return (0);
	}
	return (1);
}
