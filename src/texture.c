/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirberna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:36:16 by mirberna          #+#    #+#             */
/*   Updated: 2025/05/02 17:36:33 by mirberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	load_texture(t_cub3d *cub3d, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(cub3d->mlx_ptr, path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		ft_putstr_fd("Error\nCould not load texture\n", 2);
		exit(1);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
}

void	load_all_textures(t_cub3d *cub3d)
{
	load_texture(cub3d, &cub3d->m.texture_north, cub3d->m.path_north);
	load_texture(cub3d, &cub3d->m.texture_south, cub3d->m.path_south);
	load_texture(cub3d, &cub3d->m.texture_west, cub3d->m.path_to_west);
	load_texture(cub3d, &cub3d->m.texture_east, cub3d->m.path_east);
}

int	get_pixel_color(t_img *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(int *)pixel);
}

