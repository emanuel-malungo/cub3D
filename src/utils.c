/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:42:52 by emalungo          #+#    #+#             */
/*   Updated: 2025/06/24 09:24:24 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_cub3d	*init_cub3d(int argc, char **argv)
{
	t_cub3d	*cub3d;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d <map.cub>\n", 2);
		return (NULL);
	}
	if (!check_extension(argv[1]))
		return (NULL);
	cub3d = (t_cub3d *)malloc(sizeof(t_cub3d));
	if (!cub3d)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		return (NULL);
	}
	ft_bzero(cub3d, sizeof(t_cub3d));
	cub3d->fd = open(argv[1], O_RDONLY);
	if (cub3d->fd < 0)
	{
		free(cub3d);
		ft_putstr_fd("Error\nCould not open file\n", 2);
		return (0);
	}
	return (cub3d);
}