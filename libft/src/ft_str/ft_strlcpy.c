/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:24:57 by sviallon          #+#    #+#             */
/*   Updated: 2024/05/22 11:49:49 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t siz)
{
	size_t	i;

	if (siz <= 0)
		return (ft_strlen(src));
	i = 0;
	while (i < (siz - 1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (siz > 0)
		dest[i] = '\0';
	return (ft_strlen(src));
}
