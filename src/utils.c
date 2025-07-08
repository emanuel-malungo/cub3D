/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:42:52 by emalungo          #+#    #+#             */
/*   Updated: 2025/07/08 11:43:14 by emalungo         ###   ########.fr       */
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
	cub3d->fd = -1;
	cub3d->fd = open(argv[1], O_RDONLY);
	if (cub3d->fd < 0)
	{
		free(cub3d);
		ft_putstr_fd("Error\nCould not open file\n", 2);
		return (0);
	}
	return (cub3d);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	cleanup_cub3d(t_cub3d *cub3d)
{
	if (!cub3d)
		return ;
	if (cub3d->fd >= 0)
		close(cub3d->fd);
	if (cub3d->file_content)
		ft_free_matrix(cub3d->file_content);
	if (cub3d->m.map_content)
		ft_free_matrix(cub3d->m.map_content);
	if (cub3d->t.path_north)
		free(cub3d->t.path_north);
	if (cub3d->t.path_east)
		free(cub3d->t.path_east);
	if (cub3d->t.path_south)
		free(cub3d->t.path_south);
	if (cub3d->t.path_west)
		free(cub3d->t.path_west);
	if (cub3d->m.floor_color)
		free(cub3d->m.floor_color);
	if (cub3d->m.ceiling_color)
		free(cub3d->m.ceiling_color);
	free(cub3d);
}
