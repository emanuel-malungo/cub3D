/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 01:07:52 by emalungo          #+#    #+#             */
/*   Updated: 2025/04/27 16:57:38 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
 * Escreve um pixel na imagem (buffer) na posição (x, y)
 */
 void my_mlx_pixel_put(t_img *img, int x, int y, int color)
 {
     char *dst;
 
     dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
     *(unsigned int *)dst = color;
 }
 
 /*
  * Desenha um quadrado na posição (x, y) com tamanho e cor especificados.
  * Usa o buffer de imagem para evitar flickering.
  */
 void draw_square(t_cub3d *cub3d, int x, int y, int size, int color)
 {
     int i, j;
 
     for (i = y; i < y + size; i++)
     {
         for (j = x; j < x + size; j++)
         {
             if (i >= 0 && i < HEIGHT && j >= 0 && j < WIDTH)
                 my_mlx_pixel_put(&cub3d->img, j, i, color);
         }
     }
 }
 
 /*
  * Desenha uma linha vertical na posição x, do ponto drawStart até drawEnd, com a cor especificada.
  */
 void draw_vertical_line(t_cub3d *cub3d, int x, int drawStart, int drawEnd, int color)
 {
     int y;
     for (y = drawStart; y <= drawEnd; y++)
     {
         my_mlx_pixel_put(&cub3d->img, x, y, color);
     }
 }
 
 /*
  * Função de raycasting: para cada coluna da tela, lança um raio e detecta a colisão com a parede,
  * calculando a altura da parede a ser desenhada com base na distância.
  */
 void cast_rays(t_cub3d *cub3d)
 {
     int x;
     for (x = 0; x < WIDTH; x++)
     {
         // 1. Calcula a posição da câmera para a coluna x (-1 a 1)
         double cameraX = 2 * x / (double)WIDTH - 1;
         
         // 2. Determina a direção do raio para esta coluna
         double rayDirX = cub3d->p.dirX + cub3d->p.planeX * cameraX;
        //  printf("rayDirX: %f\n", rayDirX);
         double rayDirY = cub3d->p.dirY + cub3d->p.planeY * cameraX;
        // printf("rayDirY: %f\n", rayDirY);
         
         // 3. Posição atual no grid (mapa)
         int mapX = (int)cub3d->p.posX;
         int mapY = (int)cub3d->p.posY;
         
         // 4. Calcula as distâncias incrementais para atravessar uma célula do mapa
         double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        //  printf("deltaDistX: %f\n", deltaDistX);
         double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        // printf("deltaDistY: %f\n", deltaDistY);
         double sideDistX, sideDistY;
         int stepX, stepY;
         
         // 5. Determina o passo e a distância inicial para X
         if (rayDirX < 0)
         {
             stepX = -1;
             sideDistX = (cub3d->p.posX - mapX) * deltaDistX;
            //  printf("sideDistX: %f\n", sideDistX);
         }
         else
         {
             stepX = 1;
             sideDistX = (mapX + 1.0 - cub3d->p.posX) * deltaDistX;
                // printf("sideDistX: %f\n", sideDistX);
         }
         // Determina o passo e a distância inicial para Y
         if (rayDirY < 0)
         {
             stepY = -1;
             sideDistY = (cub3d->p.posY - mapY) * deltaDistY;
            //  printf("sideDistY: %f\n", sideDistY);
         }
         else
         {
             stepY = 1;
             sideDistY = (mapY + 1.0 - cub3d->p.posY) * deltaDistY;
                // printf("sideDistY: %f\n", sideDistY);
         }
         
         // 6. Executa o loop DDA para encontrar a parede
         int hit = 0;  // flag de colisão
         int side;     // 0 para colisão com parede vertical, 1 para horizontal
         while (hit == 0)
         {
             if (sideDistX < sideDistY)
             {
                 sideDistX += deltaDistX;
                 mapX += stepX;
                 side = 0;
             }
             else
             {
                 sideDistY += deltaDistY;
                 mapY += stepY;
                 side = 1;
             }
             // Se a célula atual do mapa for '1', temos uma parede
             if (cub3d->m.map[mapY][mapX] == '1')
                 hit = 1;
         }
         
         // 7. Calcula a distância perpendicular até a parede (para evitar o efeito "fish-eye")
         double perpWallDist;
         if (side == 0)
             perpWallDist = (mapX - cub3d->p.posX + (1 - stepX) / 2.0) / rayDirX;
         else
             perpWallDist = (mapY - cub3d->p.posY + (1 - stepY) / 2.0) / rayDirY;
         
         // 8. Calcula a altura da parede a ser desenhada com base na distância
         int lineHeight = (int)(HEIGHT / perpWallDist);
         
         // Calcula os limites para desenhar a coluna
         int drawStart = -lineHeight / 2 + HEIGHT / 2;
         if (drawStart < 0)
             drawStart = 0;
         int drawEnd = lineHeight / 2 + HEIGHT / 2;
         if (drawEnd >= HEIGHT)
             drawEnd = HEIGHT - 1;
         
         // 9. Escolhe a cor (aplicando sombreamento com base no lado)
         int color;
         if (side == 0)
             color = WALL_COLOR;  // Usa a cor definida para paredes
         else
             color = WALL_COLOR - 0x202020;  // Tom mais escuro para o outro lado
         
         // 10. Desenha a coluna vertical correspondente na posição x
         draw_vertical_line(cub3d, x, drawStart, drawEnd, color);
     }
 }
 
 /*
  * Renderiza a cena: cria um buffer off-screen, preenche o fundo,
  * chama o raycasting para desenhar as paredes e exibe a imagem na janela.
  */
 int render_map(t_cub3d *cub3d)
 {
     int x, y;
     
     // Se existir uma imagem anterior, destrói-a
     if (cub3d->img.img)
         mlx_destroy_image(cub3d->mlx_ptr, cub3d->img.img);
     // Cria uma nova imagem para o buffer
     cub3d->img.img = mlx_new_image(cub3d->mlx_ptr, WIDTH, HEIGHT);
     cub3d->img.addr = mlx_get_data_addr(cub3d->img.img,
             &cub3d->img.bits_per_pixel, &cub3d->img.line_length, &cub3d->img.endian);
     
     // Preenche o fundo com BACKGROUND_COLOR
     for (y = 0; y < HEIGHT; y++) {
         for (x = 0; x < WIDTH; x++) {
             my_mlx_pixel_put(&cub3d->img, x, y, BACKGROUND_COLOR);
         }
     }
     
     // Executa o raycasting para renderizar a cena 3D
     cast_rays(cub3d);
     
     // Exibe a imagem completa na janela
     mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->mlx_win_ptr, cub3d->img.img, 0, 0);
     
     return (0);
 }
 
