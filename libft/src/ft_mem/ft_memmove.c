/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:04:43 by sviallon          #+#    #+#             */
/*   Updated: 2024/05/30 23:52:32 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*char_dest;
	char	*char_src;

	char_dest = (char *) dest;
	char_src = (char *) src;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (char_dest < char_src)
	{
		while (i < n)
		{
			char_dest[i] = char_src[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			char_dest[n] = char_src[n];
	}
	return (dest);
}
