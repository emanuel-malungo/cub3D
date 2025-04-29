/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:31:37 by emalungo          #+#    #+#             */
/*   Updated: 2025/04/29 09:52:20 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_extension(char *file)
{
	int		len;
	char	*temp;

	len = ft_strlen(file);
	temp = ft_substr(file, len - 4, 4);
	if (ft_strncmp(temp, ".cub", 4) == 0)
	{
		free(temp);
		return (1);
	}
	else
	{
		free(temp);
		return (0);
	}
	return (0);
}

t_cub3d	*init_cub3d(int argc, char **argv)
{
	t_cub3d *cub3d;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d <map.cub>\n", 2);
		return (NULL);
	}
    if (!check_extension(argv[1]))
    {
        ft_putstr_fd("Error\nInvalid file extension. Use .cub\n", 2);
        return (NULL);
    }
	cub3d = (t_cub3d *)malloc(sizeof(t_cub3d));
	if (!cub3d)
    {
        ft_putstr_fd("Error\nMemory allocation failed\n", 2);
        return (NULL);
    }
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
