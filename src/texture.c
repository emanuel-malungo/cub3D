/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:24:25 by emalungo          #+#    #+#             */
/*   Updated: 2025/07/08 12:43:55 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	lead_texture(t_cub3d *cub3d)
{
	int	img_width;
	int	img_height;

	img_width = 0;
	img_height = 0;
	cub3d->t.img_n = mlx_xpm_file_to_image(cub3d->mlx_ptr, cub3d->t.path_north,
			&img_width, &img_height);
	cub3d->t.img_s = mlx_xpm_file_to_image(cub3d->mlx_ptr, cub3d->t.path_south,
			&img_width, &img_height);
	cub3d->t.img_e = mlx_xpm_file_to_image(cub3d->mlx_ptr, cub3d->t.path_east,
			&img_width, &img_height);
	cub3d->t.img_w = mlx_xpm_file_to_image(cub3d->mlx_ptr, cub3d->t.path_west,
			&img_width, &img_height);
	if (!cub3d->t.img_n || !cub3d->t.img_s || !cub3d->t.img_e
		|| !cub3d->t.img_w)
	{
		ft_putstr_fd("Error\nCheck the texture paths and .xpm files.\n", 2);
		return (0);
	}
	cub3d->i.img = mlx_new_image(cub3d->mlx_ptr, WIDTH_SCREEN, HEIGHT_SCREEN);
	cub3d->i.addr = mlx_get_data_addr(cub3d->i.img, &cub3d->i.bits_per_pixel,
			&cub3d->i.line_length, &cub3d->i.endian);
	return (1);
}
