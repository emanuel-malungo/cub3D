/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:17:13 by emalungo          #+#    #+#             */
/*   Updated: 2025/03/16 08:13:05 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_cub3d	*init_cub3d(void)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)malloc(sizeof(t_cub3d));
	if (!cub3d)
		return (NULL);
	ft_bzero(cub3d, sizeof(t_cub3d));
	return (cub3d);
}

static void	handle_map_line(t_cub3d *cub3d, char *line, int *map_index)
{
	cub3d->m.map = ft_realloc(cub3d->m.map, (*map_index + 2) * sizeof(char *),
			(*map_index) * sizeof(char *));
	cub3d->m.map[*map_index] = ft_strdup(line);
	(*map_index)++;
	cub3d->m.map[*map_index] = NULL;
}

void	parse_content_file(t_cub3d *cub3d)
{
	int	i;
	int	map_index;

	i = 0;
	map_index = 0;
	while (cub3d->m.content[i])
	{
		if (ft_strncmp(cub3d->m.content[i], "NO ", 3) == 0)
			cub3d->m.path_north = ft_strdup(cub3d->m.content[i] + 3);
		else if (ft_strncmp(cub3d->m.content[i], "SO ", 3) == 0)
			cub3d->m.path_south = ft_strdup(cub3d->m.content[i] + 3);
		else if (ft_strncmp(cub3d->m.content[i], "WE ", 3) == 0)
			cub3d->m.path_to_west = ft_strdup(cub3d->m.content[i] + 3);
		else if (ft_strncmp(cub3d->m.content[i], "EA ", 3) == 0)
			cub3d->m.path_east = ft_strdup(cub3d->m.content[i] + 3);
		else if (ft_strncmp(cub3d->m.content[i], "F ", 2) == 0)
			cub3d->m.floor_color = ft_strdup(cub3d->m.content[i] + 2);
		else if (ft_strncmp(cub3d->m.content[i], "C ", 2) == 0)
			cub3d->m.ceiling_color = ft_strdup(cub3d->m.content[i] + 2);
		else if (cub3d->m.content[i][0] == '1' || cub3d->m.content[i][0] == '0')
			handle_map_line(cub3d, cub3d->m.content[i], &map_index);
		i++;
	}
}

int	read_file(t_cub3d *cub3d)
{
	char	*line;
	char	*full_text;
	char	*temp;

	full_text = NULL;
	while ((line = get_next_line(cub3d->m.fd)) != NULL)
	{
		if (full_text)
		{
			temp = ft_strjoin(full_text, line);
			free(full_text);
			full_text = temp;
		}
		else
			full_text = ft_strdup(line);
		free(line);
	}
	if (!full_text)
	{
		ft_putstr_fd("Erro:\nCould not read file\n", 2);
		return (0);
	}
	cub3d->m.content = ft_split(full_text, '\n');
	free(full_text);
	return (1);
}

// funcao para pegar a posicao do player
void get_player_position(t_cub3d *cub3d)
{
	int i, j;

	for (i = 0; cub3d->m.map[i] != NULL; i++)
	{
		for (j = 0; cub3d->m.map[i][j] != '\0'; j++)
		{
			if (ft_strchr("NSEW", cub3d->m.map[i][j]))
			{
				cub3d->p.posX = j + 0.5;
				cub3d->p.posY = i + 0.5;
				if (cub3d->m.map[i][j] == 'N')
				{
					cub3d->p.dirY = -1;
					cub3d->p.planeX = 0.66;
				}
				else if (cub3d->m.map[i][j] == 'S')
				{
					cub3d->p.dirY = 1;
					cub3d->p.planeX = -0.66;
				}
				else if (cub3d->m.map[i][j] == 'E')
				{
					cub3d->p.dirX = 1;
					cub3d->p.planeY = 0.66;
				}
				else if (cub3d->m.map[i][j] == 'W')
				{
					cub3d->p.dirX = -1;
					cub3d->p.planeY = -0.66;
				}
				return;
			}
		}
	}
}

int handle_key_press(int keycode, t_cub3d *cub3d)
{
    double moveSpeed = 0.1;
    double rotSpeed = 0.05;
    double oldDirX, oldPlaneX;
    double originalX, originalY, newX, newY;

    originalX = cub3d->p.posX;
    originalY = cub3d->p.posY;

    if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A || keycode == KEY_D)
    {
        double moveX = cub3d->p.dirX * moveSpeed;
        double moveY = cub3d->p.dirY * moveSpeed;
        
        if (keycode == KEY_S) {
            moveX = -moveX;
            moveY = -moveY;
        }
        else if (keycode == KEY_D) {
            moveX = cub3d->p.dirY * moveSpeed;
            moveY = -cub3d->p.dirX * moveSpeed;
        }
        else if (keycode == KEY_A) {
            moveX = -cub3d->p.dirY * moveSpeed;
            moveY = cub3d->p.dirX * moveSpeed;
        }

        newX = originalX + moveX;
        newY = originalY + moveY;

        // Verifica colisões usando a posição original
        if (cub3d->m.map[(int)originalY][(int)newX] != '1')
            cub3d->p.posX = newX;
        if (cub3d->m.map[(int)newY][(int)originalX] != '1')
            cub3d->p.posY = newY;
    }
    else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
    {
        double rot = (keycode == KEY_LEFT) ? rotSpeed : -rotSpeed;
        oldDirX = cub3d->p.dirX;
        cub3d->p.dirX = cub3d->p.dirX * cos(rot) - cub3d->p.dirY * sin(rot);
        cub3d->p.dirY = oldDirX * sin(rot) + cub3d->p.dirY * cos(rot);
        
        oldPlaneX = cub3d->p.planeX;
        cub3d->p.planeX = cub3d->p.planeX * cos(rot) - cub3d->p.planeY * sin(rot);
        cub3d->p.planeY = oldPlaneX * sin(rot) + cub3d->p.planeY * cos(rot);
    }
    else if (keycode == KEY_ESC)
        exit(0);

    return (0);
}


int init_game(t_cub3d *cub3d)
{
    cub3d->mlx_ptr = mlx_init();
    if (!cub3d->mlx_ptr)
    {
        ft_putstr_fd("Error:\nCould not initialize mlx\n", 2);
        return (0);
    }
    cub3d->mlx_win_ptr = mlx_new_window(cub3d->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
    if (!cub3d->mlx_win_ptr)
    {
        ft_putstr_fd("Error:\nCould not create window\n", 2);
        return (0);
    }
    get_player_position(cub3d);
    mlx_hook(cub3d->mlx_win_ptr, 2, 1L<<0, handle_key_press, cub3d);
    mlx_loop_hook(cub3d->mlx_ptr, render_map, cub3d);
    mlx_loop(cub3d->mlx_ptr);
    return (1);
}


