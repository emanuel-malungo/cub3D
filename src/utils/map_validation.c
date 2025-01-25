/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:23:00 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/25 22:34:22 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_extension(const char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4)
		return (0);
	if (str[len - 4] == '.' && str[len - 3] == 'c')
	{
		if (str[len - 2] == 'u' && str[len - 1] == 'b')
			return (1);
		return (0);
	}
	return (0);
}
