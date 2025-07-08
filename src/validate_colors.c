/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:50:02 by emalungo          #+#    #+#             */
/*   Updated: 2025/07/03 02:56:30 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static int	validate_color_format(char **values, char *type)
{
	int	i;
	int	color;

	i = -1;
	while (values[++i])
	{
		if (!is_digit_string(values[i]))
		{
			ft_putstr_fd("Error:\nInvalid ", 2);
			ft_putstr_fd(type, 2);
			ft_putstr_fd(" color: non-digit value detected\n", 2);
			return (0);
		}
		color = ft_atoi(values[i]);
		if (color < 0 || color > 255)
		{
			ft_putstr_fd("Error:\nInvalid ", 2);
			ft_putstr_fd(type, 2);
			ft_putstr_fd(" color: value out of range (0-255)\n", 2);
			return (0);
		}
	}
	if (i != 3)
	{
		ft_putstr_fd("Error:\nInvalid ", 2);
		ft_putstr_fd(type, 2);
		ft_putstr_fd(" color: must have exactly 3 components (R,G,B)\n", 2);
		return (0);
	}
	return (1);
}

int	comma_number(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

void	validate_colors(t_cub3d *cub3d)
{
	char	**values;

	if (comma_number(cub3d->m.floor_color) != 2)
	{
		ft_putstr_fd("Error:\nInvalid floor color format: expected 2 commas\n", 2);
		cleanup_cub3d(cub3d);
		exit(1);
	}
	values = ft_split(cub3d->m.floor_color, ',');
	if (!values || !validate_color_format(values, "floor"))
	{
		ft_free_matrix(values);
		exit(1);
	}
	ft_free_matrix(values);

	if (comma_number(cub3d->m.ceiling_color) != 2)
	{
		ft_putstr_fd("Error:\nInvalid ceiling color format: expected 2 commas\n", 2);
		cleanup_cub3d(cub3d);
		exit(1);
	}
	values = ft_split(cub3d->m.ceiling_color, ',');
	if (!values || !validate_color_format(values, "ceiling"))
	{
		ft_free_matrix(values);
		cleanup_cub3d(cub3d);
		exit(1);
	}
	ft_free_matrix(values);
}
