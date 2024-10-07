/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:13:26 by sviallon          #+#    #+#             */
/*   Updated: 2024/05/22 13:16:09 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i] && i < siz)
		i++;
	if (i == siz)
		return (siz + ft_strlen(src));
	j = 0;
	while (src[j] && (j + i + 1 < siz))
	{
		dst[i + j] = src[j];
		j++;
	}
	if ((j + i) < siz)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
