/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:30:44 by sviallon          #+#    #+#             */
/*   Updated: 2024/05/31 11:07:13 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*dest;
	size_t			i;
	size_t			len;

	i = 0;
	len = size * nmemb;
	if (nmemb != 0 && size != 0 && (SIZE_MAX / size < nmemb))
		return (NULL);
	dest = (unsigned char *)malloc(len);
	if (!(dest))
		return (NULL);
	while (i < nmemb * size)
	{
		dest[i] = 0;
		i++;
	}
	return ((void *)dest);
}
