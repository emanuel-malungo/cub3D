/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:28:31 by emalungo          #+#    #+#             */
/*   Updated: 2025/06/30 12:28:08 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;
	int		i;

	cub3d = init_cub3d(argc, argv);
	if (!cub3d)
		return (1);
	if (!parse(cub3d))
	{
		write(2, "aaaaa", 5);
		close(cub3d->fd);
		free(cub3d->m.path_north);
		free(cub3d->m.path_east);
		free(cub3d->m.path_south);
		free(cub3d->m.floor_color);
		free(cub3d->m.ceiling_color);
		free(cub3d);
		return (1);
	}
	printf("Path north: %s\n", cub3d->m.path_north);
	printf("Path east: %s\n", cub3d->m.path_east);
	printf("Path south: %s\n", cub3d->m.path_south);
	printf("Path west: %s\n", cub3d->m.path_west);
	printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
	printf("Path floor color: %s\n", cub3d->m.floor_color);
	printf("Path ceiling color: %s\n", cub3d->m.ceiling_color);
	printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
	i = -1;
	while (cub3d->m.map_content[++i])
		printf("%s\n", cub3d->m.map_content[i]);
	close(cub3d->fd);
	ft_free_matrix(cub3d->file_content);
	ft_free_matrix(cub3d->m.map_content);
	// free(cub3d->m.path_north);
	// free(cub3d->m.path_east);
	// free(cub3d->m.path_south);
	// free(cub3d->m.path_west);
	// free(cub3d->m.floor_color);
	// free(cub3d->m.ceiling_color);
	// free(cub3d);
	printf("Sucess\n");
	return (0);
}
