/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:59:18 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/14 15:15:18 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_hexalen(unsigned long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}

void	ft_putnbr_hexa(unsigned long n, const char conversions)
{
	if (n >= 16)
	{
		ft_putnbr_hexa(n / 16, conversions);
		ft_putnbr_hexa(n % 16, conversions);
	}
	else
	{
		if (n < 10)
			ft_putchar(n + '0');
		else
		{
			if (conversions == 'x' || conversions == 'p')
				ft_putchar(n + 'a' - 10);
			else if (conversions == 'X')
				ft_putchar(n + 'A' - 10);
		}
	}
}

int	ft_printhexa(unsigned int num, const char conversions)
{
	if (num == 0)
		return (ft_putchar('0'));
	else
		ft_putnbr_hexa(num, conversions);
	return (ft_hexalen(num));
}
