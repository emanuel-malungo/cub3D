/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:41:14 by emalungo          #+#    #+#             */
/*   Updated: 2025/07/01 12:03:26 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_elements_map(char **map)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = -1;
	count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				count++;
			}
		}
	}
	if (count > 1)
	{
		ft_putstr_fd("Error\nMap must have exactly one player\n", 2);
		return (0);
	}
	return (1);
}

void	get_map_size(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	cub3d->m.heigth = 0;
	while (cub3d->m.map_content[i])
	{
		j = 0;
		while (cub3d->m.map_content[i][j])
			j++;
		if (j > cub3d->m.heigth)
			cub3d->m.heigth = j;
		i++;
	}
	cub3d->m.width = i;
}

int	check_map_wall(t_cub3d *cub3d)
{
	int	i;
	int	last_row;
	int	len;

	get_map_size(cub3d);
	last_row = cub3d->m.width - 1;
	i = -1;
	while (cub3d->m.map_content[0][++i])
	{
		if (cub3d->m.map_content[0][i] != '1'
			&& cub3d->m.map_content[0][i] != ' ')
		{
			ft_putstr_fd("Error\nMap is not surrounded by walls\n", 2);
			return (0);
		}
	}
	i = -1;
	while (cub3d->m.map_content[last_row][++i])
	{
		if (cub3d->m.map_content[last_row][i] != '1'
			&& cub3d->m.map_content[last_row][i] != ' ')
		{
			ft_putstr_fd("Error\nMap is not surrounded by walls\n", 2);
			return (0);
		}
	}
	i = -1;
	while (++i <= last_row)
	{
		if (!cub3d->m.map_content[i] || cub3d->m.map_content[i][0] == '\0')
			continue ;
		len = ft_strlen(cub3d->m.map_content[i]);
		if ((cub3d->m.map_content[i][0] != '1'
				&& cub3d->m.map_content[i][0] != ' ')
			|| (cub3d->m.map_content[i][len - 1] != '1'
				&& cub3d->m.map_content[i][len - 1] != ' '))
		{
			ft_putstr_fd("Error\nMap is not surrounded by walls\n", 2);
			return (0);
		}
	}
	return (1);
}
