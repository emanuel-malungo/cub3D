/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:19:17 by emalungo          #+#    #+#             */
/*   Updated: 2025/06/30 10:28:44 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_extension(char *str)
{
	int		len;
	char	*temp;

	len = ft_strlen(str);
	temp = ft_substr(str, len - 4, 4);
	if (ft_strncmp(temp, ".cub", 4) != 0)
	{
		free(temp);
		ft_putstr_fd("Error\nInvalid file extension. Use .cub\n", 2);
		return (0);
	}
	free(temp);
	return (1);
}

int	check_required_identifiers(t_cub3d *cub3d)
{
	int	i;
	int	count_no;
	int	count_so;
	int	count_we;
	int	count_ea;
	int	count_f;
	int	count_c;

	i = 0;
	count_no = 0;
	count_so = 0;
	count_we = 0;
	count_ea = 0;
	count_f = 0;
	count_c = 0;
	while (cub3d->file_content[i])
	{
		if (ft_strncmp(cub3d->file_content[i], "NO ", 3) == 0)
			count_no++;
		else if (ft_strncmp(cub3d->file_content[i], "SO ", 3) == 0)
			count_so++;
		else if (ft_strncmp(cub3d->file_content[i], "WE ", 3) == 0)
			count_we++;
		else if (ft_strncmp(cub3d->file_content[i], "EA ", 3) == 0)
			count_ea++;
		else if (ft_strncmp(cub3d->file_content[i], "F ", 2) == 0)
			count_f++;
		else if (ft_strncmp(cub3d->file_content[i], "C ", 2) == 0)
			count_c++;
		i++;
	}
	if (count_no != 1)
	{
		ft_putstr_fd("Error\nMissing or duplicated element: NO\n", 2);
		return (0);
	}
	if (count_so != 1)
	{
		ft_putstr_fd("Error\nMissing or duplicated element: SO\n", 2);
		return (0);
	}
	if (count_we != 1)
	{
		ft_putstr_fd("Error\nMissing or duplicated element: WE\n", 2);
		return (0);
	}
	if (count_ea != 1)
	{
		ft_putstr_fd("Error\nMissing or duplicated element: EA\n", 2);
		return (0);
	}
	if (count_f != 1)
	{
		ft_putstr_fd("Error\nMissing or duplicated element: F (floor color)\n",
			2);
		return (0);
	}
	if (count_c != 1)
	{
		ft_putstr_fd("Error\nMissing or duplicated element: C (ceiling color)\n",
			2);
		return (0);
	}
	return (1);
}