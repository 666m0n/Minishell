/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:57:45 by sviallon          #+#    #+#             */
/*   Updated: 2024/05/30 21:54:38 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long	i;
	long	nbr;
	int		isneg;

	i = 0;
	nbr = 0;
	isneg = 0;
	while (nptr[i] != '\0' && (nptr[i] == 32 || nptr[i] == '\t'
			|| nptr[i] == '\n'
			|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f'))
		i++;
	if (nptr[i] != '\0' && nptr[i] == '-')
	{
		isneg = 1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && (nptr[i] >= '0' && nptr[i] <= '9' ))
		nbr = (nbr * 10) + (nptr[i++] - '0');
	if (isneg == 1)
		return (-nbr);
	return (nbr);
}

/*#include <stdio.h>

int	main(void)
{
	const char	*nptr = "+6784";

	printf("%d %d", ft_atoi(nptr), atoi(nptr));
	return (0);
}*/