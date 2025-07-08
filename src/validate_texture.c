/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:46:27 by emalungo          #+#    #+#             */
/*   Updated: 2025/07/08 11:33:08 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_valid_path(const char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	validate_texture_paths(t_cub3d *cub3d)
{
	if (!is_valid_path(cub3d->t.path_north))
	{
		ft_putstr_fd("Error: Invalid texture path (north)\n", 2);
		return (0);
	}
	if (!is_valid_path(cub3d->t.path_east))
	{
		ft_putstr_fd("Error: Invalid texture path (east)\n", 2);
		return (0);
	}
	if (!is_valid_path(cub3d->t.path_south))
	{
		ft_putstr_fd("Error: Invalid texture path (south)\n", 2);
		return (0);
	}
	if (!is_valid_path(cub3d->t.path_west))
	{
		ft_putstr_fd("Error: Invalid texture path (west)\n", 2);
		return (0);
	}
	return (1);
}

