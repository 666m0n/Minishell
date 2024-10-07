/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_msc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:14:47 by sviallon          #+#    #+#             */
/*   Updated: 2024/06/06 14:39:35 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../include/libft.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr(int nb)
{
	long long	n;

	n = nb;
	if (nb < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		ft_putchar(n + '0');
	}
	return (ft_intlen(nb));
}

int	ft_intlen(long long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_printptr(void *n, const char conversions)
{
	int			len;
	long long	nb;

	nb = (long long)n;
	len = 0;
	if (nb == 0)
	{
		len += ft_putstr("(nil)");
		return (len);
	}
	len += ft_putchar('0');
	len += ft_putchar('x');
	ft_putnbr_hexa(nb, conversions);
	return (len + ft_hexalen(nb));
}
