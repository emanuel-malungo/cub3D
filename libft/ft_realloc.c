/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:07:45 by emalungo          #+#    #+#             */
/*   Updated: 2025/03/16 00:07:59 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
    void	*new_ptr;

    new_ptr = malloc(new_size);
    if (!new_ptr)
    {
        free(ptr);
        return (NULL);
    }
    ft_memcpy(new_ptr, ptr, old_size);
    free(ptr);
    return (new_ptr);
}