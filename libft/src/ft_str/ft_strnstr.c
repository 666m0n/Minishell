/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:07:02 by sviallon          #+#    #+#             */
/*   Updated: 2024/05/31 00:55:24 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	lilen;

	i = 0;
	j = 0;
	lilen = ft_strlen(little);
	if (lilen == 0 || big == little)
		return ((char *)big);
	while (big[i] && i < len)
	{
		while (big[i + j] == little[j] && big[i + j] && little[j]
			&& (i + j) < len)
		{
			j++;
			if (j == lilen)
				return ((char *)&big[i]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>

int	main(void)
{
	const char	*big = "lorem ipsum dolor sit amet";
	const char	*little = "ipsumm";
	size_t		len = 30;
	char		*result;

	result = ft_strnstr(big, little, len);
	if (result != NULL)
		printf("substring found : %s\n", result);
	else
		printf("substring not found. \n");
	return (0);
}*/