/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:52:56 by sviallon          #+#    #+#             */
/*   Updated: 2024/07/03 18:29:25 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	st;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	else if ((ft_strlen(s) - start) < len)
	{
		len = ft_strlen(s) - start;
	}
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!(dest))
		return (NULL);
	st = 0;
	while (st < len && s[start + st])
	{
		dest[st] = s[start + st];
		st++;
	}
	dest[st] = '\0';
	return (dest);
}
