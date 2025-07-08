/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:28:31 by emalungo          #+#    #+#             */
/*   Updated: 2025/07/08 13:23:29 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"



int	init_game(t_cub3d *cub3d)
{
	cub3d->mlx_ptr = mlx_init();
	if (!cub3d->mlx_ptr)
	{
		ft_putstr_fd("Error\nCould not initialize mlx\n", 2);
		return (0);
	}
	cub3d->mlx_win_ptr = mlx_new_window(cub3d->mlx_ptr, WIDTH_SCREEN,
			HEIGHT_SCREEN, "Cub3d");
	if (!cub3d->mlx_win_ptr)
	{
		ft_putstr_fd("Error\nCould not create window\n", 2);
		return (0);
	}
	if (!lead_texture(cub3d))
		return (0);
	mlx_hook(cub3d->mlx_win_ptr, 2, 1L << 0, handle_key_press, cub3d);
	mlx_loop_hook(cub3d->mlx_ptr, ray_casting, cub3d);
	mlx_loop(cub3d->mlx_ptr);
	return (1);
}

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;
	// int		i;

	cub3d = init_cub3d(argc, argv);
	if (!cub3d)
		return (1);
	if (!parse(cub3d))
	{
		cleanup_cub3d(cub3d);
		return (1);
	}
	// printf("Path north: %s\n", cub3d->t.path_north);
	// printf("Path east: %s\n", cub3d->t.path_east);
	// printf("Path south: %s\n", cub3d->t.path_south);
	// printf("Path west: %s\n", cub3d->t.path_west);
	// printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
	// printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
	// printf("Path floor color: %s\n", cub3d->m.floor_color);
	// printf("Path ceiling color: %s\n", cub3d->m.ceiling_color);
	// printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
	// printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
	// i = -1;
	// while (cub3d->m.map_content[++i])
	// 	printf("%s\n", cub3d->m.map_content[i]);
	if (init_game(cub3d))
		return (0);
	cleanup_cub3d(cub3d);
	printf("Sucess\n");
	return (0);
}
