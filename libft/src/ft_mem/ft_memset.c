/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:15:38 by sviallon          #+#    #+#             */
/*   Updated: 2024/05/22 09:42:32 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *src, int c, size_t len)
{
	unsigned char	*dest;
	size_t			i;

	dest = (unsigned char *)src;
	i = 0;
	while (i < len)
	{
		dest[i] = (unsigned char)c;
		i++;
	}
	return (src);
}
