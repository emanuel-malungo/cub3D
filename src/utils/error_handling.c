/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:02:30 by emalungo          #+#    #+#             */
/*   Updated: 2025/03/15 22:46:22 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	check_input_and_open_file(char argc, char *file, t_cub3d **cub3d)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error:\nUsage: ./cub3d <map_file>\n", 2);
		return (0);
	}
	if (!check_extension(file))
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		return (0);
	}
	*cub3d = init_cub3d();
	(*cub3d)->m.fd = open(file, O_RDONLY);
	if ((*cub3d)->m.fd < 0)
	{
		ft_putstr_fd("Error\nCould not open file\n", 2);
		free(*cub3d);
		return (0);
	}
	return (1);
}
