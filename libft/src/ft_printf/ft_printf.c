/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:55:40 by sviallon          #+#    #+#             */
/*   Updated: 2024/06/06 14:37:31 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../include/libft.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_conversions(va_list args, const char conversions)
{
	int	lenght;

	lenght = 0;
	if (conversions == 'c')
		lenght += ft_putchar(va_arg(args, int));
	else if (conversions == 's')
		lenght += ft_putstr(va_arg(args, char *));
	else if (conversions == '%')
		lenght += ft_putchar('%');
	else if (conversions == 'd' || conversions == 'i')
		lenght += ft_putnbr(va_arg(args, int));
	else if (conversions == 'x' || conversions == 'X')
		lenght += ft_printhexa(va_arg(args, unsigned int), conversions);
	else if (conversions == 'p')
		lenght += ft_printptr(va_arg(args, void *), conversions);
	else if (conversions == 'u')
		lenght += ft_putunbr(va_arg(args, unsigned int));
	return (lenght);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		lenght;

	i = 0;
	lenght = 0;
	if (!str)
		return (lenght);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
			lenght += ft_conversions(args, str[++i]);
		else
			lenght += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (lenght);
}
