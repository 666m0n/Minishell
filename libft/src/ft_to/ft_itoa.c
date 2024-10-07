/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42Paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:49:40 by sviallon          #+#    #+#             */
/*   Updated: 2024/06/03 19:39:28 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	num_len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t			len;
	char			*dest;
	unsigned int	num;

	len = num_len(n);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!(dest))
		return (NULL);
	dest[len] = '\0';
	if (n < 0)
	{
		dest[0] = '-';
		num = -n;
	}
	else
		num = n;
	while (len > 0)
	{
		len--;
		if (n < 0 && len == 0)
			break ;
		dest[len] = (num % 10) + '0';
		num /= 10;
	}
	return (dest);
}
