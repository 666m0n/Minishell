/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:54:44 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/03 16:51:31 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static int	check_prefix(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (!str || !*str)
		return (0);
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i + 1] == '+' || str[*i + 1] == '-')
			return (0);
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static t_bool	is_valid_numeric(const char *str, int start)
{
	int		i;
	t_bool	has_digit;

	i = start;
	has_digit = FALSE;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		has_digit = TRUE;
		i++;
	}
	return (has_digit);
}

static long long	ft_atoll(const char *str, t_bool *overflow)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	i = 0;
	*overflow = FALSE;
	sign = check_prefix(str, &i);
	if (!sign)
		return (0);
	while (str[i] && str[i] == '0')
		i++;
	while (str[i])
	{
		if (result > LLONG_MAX / 10
			|| (result == LLONG_MAX / 10 && (str[i] - '0') > LLONG_MAX % 10))
		{
			*overflow = TRUE;
			return (0);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	handle_numeric_arg(const char *arg)
{
	t_bool		overflow;
	long long	num;
	int			i;
	int			sign;

	i = 0;
	sign = check_prefix(arg, &i);
	if (!sign || !is_valid_numeric(arg, i))
		return (INVALID_NUMERIC_ARG);
	num = ft_atoll(arg, &overflow);
	if (overflow)
		return (INVALID_NUMERIC_ARG);
	if (num < 0)
		return (256 - (-num % 256));
	return (num % 256);
}
