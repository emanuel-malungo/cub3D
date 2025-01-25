/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:18:51 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/25 22:46:59 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	input_validation(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error:\nUsage: ./cub3d <map_file>\n", 1);
		return (0);
	}
	if (!check_extension(argv[1]))
	{
		ft_putstr_fd("Error:\nInvalid file extension.\n", 2);
		return (0);
	}
	return (1);
}