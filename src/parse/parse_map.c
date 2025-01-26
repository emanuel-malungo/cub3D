/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 00:11:59 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/26 02:37:47 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*new_ptr;

	new_ptr = NULL;
	if (!ptr)
	{
		new_ptr = malloc(new_size);
		return (new_ptr);
	}
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size <= old_size)
		return (ptr);
	new_ptr = malloc(new_size);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

void parse(t_game *game)
{
    int i;

    i = 0;
    while (game->m.content[i])
    {
        if (ft_strncmp(game->m.content[i], "NO ", 3) == 0)
            game->m.path_north = ft_strdup(game->m.content[i] + 3);
        else if (ft_strncmp(game->m.content[i], "SO ", 3) == 0)
            game->m.path_south = ft_strdup(game->m.content[i] + 3);
        else if (ft_strncmp(game->m.content[i], "WE ", 3) == 0)
            game->m.path_to_west = ft_strdup(game->m.content[i] + 3);
        else if (ft_strncmp(game->m.content[i], "EA ", 3) == 0)
            game->m.path_east = ft_strdup(game->m.content[i] + 3);
        else if (ft_strncmp(game->m.content[i], "F ", 2) == 0)
            game->m.floor_color = ft_strdup(game->m.content[i] + 2);
        else if (ft_strncmp(game->m.content[i], "C ", 2) == 0)
            game->m.ceiling_color = ft_strdup(game->m.content[i] + 2);
        else if (game->m.content[i][0] == '1' || game->m.content[i][0] == '0'
                || game->m.content[i][0] == 'N' || game->m.content[i][0] == ' ')
        {
            if (!game->m.map)
                game->m.map = ft_split(game->m.content[i], '\n');
            else
                game->m.map = ft_realloc(game->m.map, (i + 2) * sizeof(char*), (i + 1) * sizeof(char*));
            game->m.map[i] = ft_strdup(game->m.content[i]);
        }
        i++;
    }
}

void	*read_and_resize_buffer(t_game *game, size_t *t_read, size_t *buffer_s)
{
	ssize_t	bytes_r;
	char	*temp;

	bytes_r = read(game->m.fd, game->m.buffer + *t_read, *buffer_s - *t_read);
	if (bytes_r < 0)
	{
		free(game->m.buffer);
		return (NULL);
	}
	if (bytes_r == 0)
		return (NULL);
	*t_read += bytes_r;
	if (*t_read >= *buffer_s)
	{
		*buffer_s *= 2;
		temp = ft_realloc(game->m.buffer, *buffer_s, *t_read);
		if (!temp)
		{
			free(game->m.buffer);
			return (NULL);
		}
		game->m.buffer = temp;
	}
	return (game->m.buffer);
}

void	*read_map(t_game *game)
{
	char	*buffer;
	size_t	t_read;
	size_t	buffer_s;

	t_read = 0;
	buffer_s = 8024;
	buffer = (char *)malloc(sizeof(char) * buffer_s);
	if (!buffer)
		return (NULL);
	game->m.buffer = buffer;
	while (1)
	{
		if (!read_and_resize_buffer(game, &t_read, &buffer_s))
			break ;
	}
	game->m.buffer[t_read] = '\0';
	return (game->m.buffer);
}

void read_parse_file(t_game *game)
{
    if (!read_map(game) || !game->m.buffer)
    {
        ft_putstr_fd("Error:\n reading map", 2);
        exit(1);
    }

    if (game->m.buffer[0] == '\n')
    {
        free(game->m.buffer);
        ft_putstr_fd("Error:\n map cannot start with a newline\n", 2);
        exit(1);
    }

    game->m.content = ft_split(game->m.buffer, '\n');
    free(game->m.buffer);
    if (!game->m.content)
    {
        ft_putstr_fd("Error:\n splitting map\n", 2);
        exit(1);
    }
    parse(game);
	if (!check_parse(game))
		exit(1);
}
