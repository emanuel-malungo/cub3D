/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:44:06 by emalungo          #+#    #+#             */
/*   Updated: 2025/06/24 09:19:03 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	read_file(t_cub3d *cub3d)
{
	char	*line;
	char	*temp;
	char	*content;

	content = NULL;
	while ((line = get_next_line(cub3d->fd)) != NULL)
	{
		if (content)
		{
			temp = ft_strjoin(content, line);
			free(content);
			content = temp;
		}
		else
			content = ft_strdup(line);
		free(line);
	}
	if (!content)
	{
		ft_putstr_fd("Erro:\nCould not read file\n", 2);
		return (0);
	}
	cub3d->file_content = ft_split(content, '\n');
	return (1);
}

static int	parse_map_content(t_cub3d *cub3d)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	while (cub3d->file_content[i])
	{
		if (ft_strncmp(cub3d->file_content[i], "1", 1) == 0
			|| ft_strncmp(cub3d->file_content[i], "0", 1) == 0)
		{
			tmp = ft_realloc(cub3d->m.map_content, (j + 2) * sizeof(char *), j
					* sizeof(char *));
			if (!tmp)
				return (0);
			cub3d->m.map_content = tmp;
			cub3d->m.map_content[j] = ft_strdup(cub3d->file_content[i]);
			if (!cub3d->m.map_content[j])
				return (0);
			cub3d->m.map_content[j + 1] = NULL;
			j++;
		}
		i++;
	}
	return (1);
}

int	parse(t_cub3d *cub3d)
{
	int	i;

	i = -1;
	if (!read_file(cub3d))
		return (0);
	while (cub3d->file_content[++i])
	{
		if (ft_strncmp(cub3d->file_content[i], "NO ", 3) == 0)
			cub3d->m.path_north = ft_strdup(cub3d->file_content[i] + 3);
		else if (ft_strncmp(cub3d->file_content[i], "SO ", 3) == 0)
			cub3d->m.path_south = ft_strdup(cub3d->file_content[i] + 3);
		else if (ft_strncmp(cub3d->file_content[i], "WE ", 3) == 0)
			cub3d->m.path_west = ft_strdup(cub3d->file_content[i] + 3);
		else if (ft_strncmp(cub3d->file_content[i], "EA ", 3) == 0)
			cub3d->m.path_east = ft_strdup(cub3d->file_content[i] + 3);
		else if (ft_strncmp(cub3d->file_content[i], "F ", 2) == 0)
			cub3d->m.floor_color = ft_strdup(cub3d->file_content[i] + 2);
		else if (ft_strncmp(cub3d->file_content[i], "C ", 2) == 0)
			cub3d->m.ceiling_color = ft_strdup(cub3d->file_content[i] + 2);
	}
	parse_map_content(cub3d);
	return (1);
}
