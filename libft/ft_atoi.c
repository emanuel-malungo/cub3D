/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:30:23 by emalungo          #+#    #+#             */
/*   Updated: 2025/06/26 14:11:07 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	capture_the_beast(const char *str, int neg_flag, int i)
{
	long	result;
	long	previous_result;

	result = 0;
	previous_result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result < 0 || result > 255)
			return(-1);
		previous_result = result;
		result = result * 10 + str[i++] - '0';
		if (previous_result > result)
		{
			if (neg_flag < 0)
				return (0);
			else
				return (-1);
		}
	}
	return (result * neg_flag);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		neg_flag;

	i = 0;
	neg_flag = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg_flag = -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	return (capture_the_beast(str, neg_flag, i));
}
