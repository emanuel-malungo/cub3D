/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:23:11 by emalungo          #+#    #+#             */
/*   Updated: 2025/07/08 13:23:32 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int handle_key_press(int keycode, t_cub3d *cub3d)
{
    double moveSpeed = 0.05;  // Reduzido para um movimento mais suave
    double rotSpeed = 0.05;
    double oldDirX, oldPlaneX;
    double newX, newY;

    // Movimento para frente e para trás (W e S)
    if (keycode == KEY_W)
    {
        newX = cub3d->p.posX + cub3d->p.dirX * moveSpeed;
        newY = cub3d->p.posY + cub3d->p.dirY * moveSpeed;
        if (cub3d->m.map_content[(int)newY][(int)cub3d->p.posX] != '1')
            cub3d->p.posY = newY;
        if (cub3d->m.map_content[(int)cub3d->p.posY][(int)newX] != '1')
            cub3d->p.posX = newX;
    }
    else if (keycode == KEY_S)
    {
        newX = cub3d->p.posX - cub3d->p.dirX * moveSpeed;
        newY = cub3d->p.posY - cub3d->p.dirY * moveSpeed;
        if (cub3d->m.map_content[(int)newY][(int)cub3d->p.posX] != '1')
            cub3d->p.posY = newY;
        if (cub3d->m.map_content[(int)cub3d->p.posY][(int)newX] != '1')
            cub3d->p.posX = newX;
    }
    // Movimento lateral (A e D)
    else if (keycode ==  KEY_D)
    {
        // Movimento para a esquerda (perpendicular à direção)
        newX = cub3d->p.posX - cub3d->p.dirY * moveSpeed;
        newY = cub3d->p.posY + cub3d->p.dirX * moveSpeed;
        if (cub3d->m.map_content[(int)newY][(int)cub3d->p.posX] != '1')
            cub3d->p.posY = newY;
        if (cub3d->m.map_content[(int)cub3d->p.posY][(int)newX] != '1')
            cub3d->p.posX = newX;
    }
    else if (keycode == KEY_A)
    {
        // Movimento para a direita (perpendicular à direção)
        newX = cub3d->p.posX + cub3d->p.dirY * moveSpeed;
        newY = cub3d->p.posY - cub3d->p.dirX * moveSpeed;
        if (cub3d->m.map_content[(int)newY][(int)cub3d->p.posX] != '1')
            cub3d->p.posY = newY;
        if (cub3d->m.map_content[(int)cub3d->p.posY][(int)newX] != '1')
            cub3d->p.posX = newX;
    }
    // Rotação (setas esquerda e direita)
    else if (keycode == KEY_LEFT)
    {
        // Rotação para a esquerda
        oldDirX = cub3d->p.dirX;
        cub3d->p.dirX = cub3d->p.dirX * cos(rotSpeed) - cub3d->p.dirY * sin(rotSpeed);
        cub3d->p.dirY = oldDirX * sin(rotSpeed) + cub3d->p.dirY * cos(rotSpeed);
        
        oldPlaneX = cub3d->p.planeX;
        cub3d->p.planeX = cub3d->p.planeX * cos(rotSpeed) - cub3d->p.planeY * sin(rotSpeed);
        cub3d->p.planeY = oldPlaneX * sin(rotSpeed) + cub3d->p.planeY * cos(rotSpeed);
    }
    else if (keycode == KEY_RIGHT)
    {
        // Rotação para a direita
        oldDirX = cub3d->p.dirX;
        cub3d->p.dirX = cub3d->p.dirX * cos(-rotSpeed) - cub3d->p.dirY * sin(-rotSpeed);
        cub3d->p.dirY = oldDirX * sin(-rotSpeed) + cub3d->p.dirY * cos(-rotSpeed);
        
        oldPlaneX = cub3d->p.planeX;
        cub3d->p.planeX = cub3d->p.planeX * cos(-rotSpeed) - cub3d->p.planeY * sin(-rotSpeed);
        cub3d->p.planeY = oldPlaneX * sin(-rotSpeed) + cub3d->p.planeY * cos(-rotSpeed);
    }
    else if (keycode == KEY_ESC)
        exit(0);

    return (0);
}