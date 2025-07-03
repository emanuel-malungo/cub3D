/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:44:06 by emalungo          #+#    #+#             */
/*   Updated: 2025/07/03 01:07:46 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_map_line(char *line)
{
	while (*line)
	{
		if (!ft_strchr(" 01NSEW", *line))
			return (0);
		line++;
	}
	return (1);
}

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
		ft_putstr_fd("Error:\nCould not read file\n", 2);
		return (0);
	}
	cub3d->file_content = ft_split(content, '\n');
	free(content);
	if (is_map_line(cub3d->file_content[0]))
	{
		ft_free_matrix(cub3d->file_content);
		ft_putstr_fd("Error\nMap content appears before textures or colors\n", 2);
		return (0);
	}
	return (1);
}

static int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	if (!*line)  // Linha completamente vazia (apenas \n)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	validate_map_continuity(t_cub3d *cub3d)
{
	int	i;
	int	map_started;
	int	found_empty;

	i = 0;
	map_started = 0;
	found_empty = 0;
	while (cub3d->file_content[i])
	{
		if (is_map_line(cub3d->file_content[i]) && !is_empty_line(cub3d->file_content[i]))
		{
			if (found_empty && map_started)
			{
				ft_putstr_fd("Error\nMap is divided (empty line found in middle of map)\n", 2);
				return (0);
			}
			map_started = 1;
			found_empty = 0;  // Reset se encontrarmos conteúdo válido do mapa
		}
		else if (map_started && is_empty_line(cub3d->file_content[i]))
		{
			found_empty = 1;
		}
		else if (map_started && !is_map_line(cub3d->file_content[i]) && !is_empty_line(cub3d->file_content[i]))
		{
			ft_putstr_fd("Error\nInvalid content after map\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	parse_map_content(t_cub3d *cub3d)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	while (cub3d->file_content[i] && !is_map_line(cub3d->file_content[i]))
		i++;
	while (cub3d->file_content[i] && is_map_line(cub3d->file_content[i]))
	{
		tmp = ft_realloc(cub3d->m.map_content, (j + 2) * sizeof(char *), j
				* sizeof(char *));
		if (!tmp)
		{
			if (cub3d->m.map_content)
				ft_free_matrix(cub3d->m.map_content);
			cub3d->m.map_content = NULL;
			return (0);
		}
		cub3d->m.map_content = tmp;
		cub3d->m.map_content[j] = ft_strdup(cub3d->file_content[i]);
		if (!cub3d->m.map_content[j])
		{
			ft_free_matrix(cub3d->m.map_content);
			cub3d->m.map_content = NULL;
			return (0);
		}
		cub3d->m.map_content[++j] = NULL;
		i++;
	}
	return (1);
}

int	parse(t_cub3d *cub3d)
{
	int		i;
	char	*temp;

	i = -1;
	if (!read_file(cub3d))
		return (0);
	if (!check_required_identifiers(cub3d))
		return (0);
	while (cub3d->file_content[++i])
	{
		if (ft_strncmp(cub3d->file_content[i], "NO ", 3) == 0)
		{
			temp = ft_strdup(cub3d->file_content[i] + 3);
			cub3d->m.path_north = ft_strtrim(temp, " ");
			free(temp);
		}
		else if (ft_strncmp(cub3d->file_content[i], "SO ", 3) == 0)
		{
			temp = ft_strdup(cub3d->file_content[i] + 3);
			cub3d->m.path_south = ft_strtrim(temp, " ");
			free(temp);
		}
		else if (ft_strncmp(cub3d->file_content[i], "WE ", 3) == 0)
		{
			temp = ft_strdup(cub3d->file_content[i] + 3);
			cub3d->m.path_west = ft_strtrim(temp, " ");
			free(temp);
		}
		else if (ft_strncmp(cub3d->file_content[i], "EA ", 3) == 0)
		{
			temp = ft_strdup(cub3d->file_content[i] + 3);
			cub3d->m.path_east = ft_strtrim(temp, " ");
			free(temp);
		}
		else if (ft_strncmp(cub3d->file_content[i], "F ", 2) == 0)
		{
			temp = ft_strdup(cub3d->file_content[i] + 2);
			cub3d->m.floor_color = ft_strtrim(temp, " ");
			free(temp);
		}
		else if (ft_strncmp(cub3d->file_content[i], "C ", 2) == 0)
		{
			temp = ft_strdup(cub3d->file_content[i] + 2);
			cub3d->m.ceiling_color = ft_strtrim(temp, " ");
			free(temp);
		}
	}
	// if (!validate_texture_paths(cub3d))
	// 	return (0);
	validate_colors(cub3d);
	parse_map_content(cub3d);
	if (!check_elements_map(cub3d->m.map_content))
		return (0);
	if (!check_map_wall(cub3d))
		return (0);
	if (!validate_map_continuity(cub3d))
		return (0);
	return (1);
}
