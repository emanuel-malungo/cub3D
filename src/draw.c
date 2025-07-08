/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:40:59 by emalungo          #+#    #+#             */
/*   Updated: 2025/07/08 13:16:19 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_cub3d *cub3d, int x, int y, int size, int color)
{
	int	i;
	int	j;

	if (x < 0 || x >= WIDTH_SCREEN || y < 0 || y >= HEIGHT_SCREEN)
		return ;
	i = y;
	while (i < y + size)
	{
		j = x;
		while (j < x + size)
		{
			if (i >= 0 && i < HEIGHT_SCREEN && j >= 0 && j < WIDTH_SCREEN)
				my_mlx_pixel_put(&cub3d->i.img, j, i, color);
			j++;
		}
	}
}

void	draw_vertical_line(t_cub3d *cub3d, int x, int drawStart, int drawEnd, int color)
{
	int	y;

	y = drawStart;
	while (y <= drawEnd)
	{
		my_mlx_pixel_put(&cub3d->i.img, x, y, color);
		y++;
	}
}

void	draw_background(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT_SCREEN)
	{
		x = 0;
		while (x < WIDTH_SCREEN)
		{
			if (y < HEIGHT_SCREEN / 2)
				my_mlx_pixel_put(&cub3d->i.img, x, y, 0x6CB8DD);
			else
				my_mlx_pixel_put(&cub3d->i.img, x, y, 0x4A4A4A);
			x++;
		}
        y++;
	}
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
