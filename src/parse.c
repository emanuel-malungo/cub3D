/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:44:06 by emalungo          #+#    #+#             */
/*   Updated: 2025/07/08 11:32:41 by emalungo         ###   ########.fr       */
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
			cub3d->t.path_north = ft_strtrim(temp, " ");
			free(temp);
		}
		else if (ft_strncmp(cub3d->file_content[i], "SO ", 3) == 0)
		{
			temp = ft_strdup(cub3d->file_content[i] + 3);
			cub3d->t.path_south = ft_strtrim(temp, " ");
			free(temp);
		}
		else if (ft_strncmp(cub3d->file_content[i], "WE ", 3) == 0)
		{
			temp = ft_strdup(cub3d->file_content[i] + 3);
			cub3d->t.path_west = ft_strtrim(temp, " ");
			free(temp);
		}
		else if (ft_strncmp(cub3d->file_content[i], "EA ", 3) == 0)
		{
			temp = ft_strdup(cub3d->file_content[i] + 3);
			cub3d->t.path_east = ft_strtrim(temp, " ");
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
	return (1);
}
