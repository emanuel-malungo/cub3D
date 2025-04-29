/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:13:46 by emalungo          #+#    #+#             */
/*   Updated: 2025/04/29 13:18:19 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_orientario_player(t_cub3d *cub3d, char orientarion)
{
	if (orientarion == 'N')
	{
		cub3d->p.dirX = -1;
		cub3d->p.dirY = 0;
		cub3d->p.planeX = 0;
		cub3d->p.planeY = 0.66;
	}
	else if (orientarion == 'S')
	{
		cub3d->p.dirX = 1;
		cub3d->p.dirY = 0;
		cub3d->p.planeX = 0;
		cub3d->p.planeY = -0.66;
	}
	else if (orientarion == 'E')
	{
		cub3d->p.dirX = 0;
		cub3d->p.dirY = 1;
		cub3d->p.planeX = 0.66;
		cub3d->p.planeY = 0;
	}
	else if (orientarion == 'W')
	{
		cub3d->p.dirX = 0;
		cub3d->p.dirY = -1;
		cub3d->p.planeX = -0.66;
		cub3d->p.planeY = 0;
	}
}

void get_player_position(t_cub3d *cub3d)
{
    int i;
    int j;

    i = 0;
    while (cub3d->m.map[i] != NULL)
    {
        j = 0;
        while (cub3d->m.map[i][j] != '\0')
        {
            if (ft_strchr("NSWE", cub3d->m.map[i][j]))
            {
                cub3d->p.posX = j + 0.5;
                cub3d->p.posY = i + 0.5;
                set_orientario_player(cub3d, cub3d->m.map[i][j]);
                return;
            }
            j++;
        }
        i++;
    }
}
