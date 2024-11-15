/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:33:28 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/15 20:34:24 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strcat(char *dest, char *src)
{
	size_t	i;
	size_t	lengthdest;

	if (!dest || !src)
		return (0);
	lengthdest = 0;
	i = 0;
	while (dest[lengthdest])
		lengthdest++;
	while (src[i])
	{
		dest[lengthdest + i] = src[i];
		i++;
	}
	dest[lengthdest + i] = '\0';
	return (lengthdest + i);
}

size_t	ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	if (!dest || !src)
		return (0);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}
