#include "../include/cub3d.h"

void	perform_dda(t_cub3d *cub3d, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (cub3d->m.map[ray->mapY][ray->mapX] == '1')
			hit = 1;
	}
}

void	init_ray_steps(t_cub3d *cub3d, t_ray *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (cub3d->p.posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - cub3d->p.posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (cub3d->p.posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - cub3d->p.posY) * ray->deltaDistY;
	}
}

t_ray	calculate_ray(t_cub3d *cub3d, int i)
{
	t_ray	ray;

	ray.cameraX = 2 * i / (double)WIDTH_SCREEN - 1;
	ray.rayDirX = cub3d->p.dirX + cub3d->p.planeX * ray.cameraX;
	ray.rayDirY = cub3d->p.dirY + cub3d->p.planeY * ray.cameraX;
	ray.mapX = (int)cub3d->p.posX;
	ray.mapY = (int)cub3d->p.posY;
	if (ray.rayDirX == 0)
		ray.deltaDistX = 1e30;
	else
		ray.deltaDistX = fabs(1 / ray.rayDirX);
	if (ray.rayDirY == 0)
		ray.deltaDistY = 1e30;
	else
		ray.deltaDistY = fabs(1 / ray.rayDirY);
	init_ray_steps(cub3d, &ray);
	return (ray);
}

void	draw_texture_line(t_cub3d *cub3d, int x, t_ray *ray, double wallX)
{
	int		y;
	double	step;
	double	texPos;
	int		texX;
	int		texY;
	t_img	*texture;
	int		color;

	if (ray->side == 0 && ray->rayDirX > 0)
		texture = &cub3d->m.texture_west;
	else if (ray->side == 0 && ray->rayDirX < 0)
		texture = &cub3d->m.texture_east;
	else if (ray->side == 1 && ray->rayDirY > 0)
		texture = &cub3d->m.texture_north;
	else
		texture = &cub3d->m.texture_south;

	texX = (int)(wallX * (double)texture->width);
	if ((ray->side == 0 && ray->rayDirX > 0) || (ray->side == 1 && ray->rayDirY < 0))
		texX = texture->width - texX - 1;
	step = 1.0 * texture->height / ray->lineHeight;
	texPos = (ray->drawStart - HEIGHT_SCREEN / 2 + ray->lineHeight / 2) * step;
	y = ray->drawStart;
	while (y < ray->drawEnd)
	{
		texY = (int)texPos & (texture->height - 1);
		texPos += step;
		color = get_pixel_color(texture, texX, texY);
		my_mlx_pixel_put(&cub3d->img, x, y, color);
		y++;
	}
}

int	ray_casting(t_cub3d *cub3d)
{
	t_ray	ray;
	int		i;
	double	perpWallDist;
	double	wallX;

	i = 0;
	draw_background(cub3d);
	while (i < WIDTH_SCREEN)
	{
		ray = calculate_ray(cub3d, i);
		perform_dda(cub3d, &ray);
		if (ray.side == 0)
			perpWallDist = (ray.mapX - cub3d->p.posX + (1 - ray.stepX) / 2.0)
				/ ray.rayDirX;
		else
			perpWallDist = (ray.mapY - cub3d->p.posY + (1 - ray.stepY) / 2.0)
				/ ray.rayDirY;
		ray.lineHeight = (int)(HEIGHT_SCREEN / perpWallDist);
		ray.drawStart = -ray.lineHeight / 2 + HEIGHT_SCREEN / 2;
		if (ray.drawStart < 0)
			ray.drawStart = 0;
		ray.drawEnd = ray.lineHeight / 2 + HEIGHT_SCREEN / 2;
		if (ray.drawEnd >= HEIGHT_SCREEN)
			ray.drawEnd = HEIGHT_SCREEN - 1;
		if (ray.side == 0)
			wallX = cub3d->p.posY + perpWallDist * ray.rayDirY;
		else
			wallX = cub3d->p.posX + perpWallDist * ray.rayDirX;
		wallX -= floor(wallX);
		draw_texture_line(cub3d, i, &ray, wallX);
		i++;
	}
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->mlx_win_ptr,
		cub3d->img.img, 0, 0);
	return (1);
}

