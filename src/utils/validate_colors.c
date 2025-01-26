/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:50:02 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/26 14:14:22 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	is_digit_string(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	validate_color_format(char **values)
{
	int	i;
	int	color;

	i = 0;
	while (values[i])
	{
		if (!is_digit_string(values[i]))
			return (0);
		color = atoi(values[i]);
		if (color < 0 || color > 255)
			return (0);
		i++;
	}
	return (i == 3);
}

void	validate_colors(t_game *game)
{
	char	**values;

	values = ft_split(game->m.floor_color, ',');
	if (!values || !validate_color_format(values))
	{
		ft_free_split(values);
		ft_putstr_fd("Error:\nInvalid floor color format\n", 2);
		clean_game(game, 1);
	}
	ft_free_split(values);
	values = ft_split(game->m.ceiling_color, ',');
	if (!values || !validate_color_format(values))
	{
		ft_free_split(values);
		ft_putstr_fd("Error:\nInvalid ceiling color format\n", 2);
		clean_game(game, 1);
	}
	ft_free_split(values);
}
