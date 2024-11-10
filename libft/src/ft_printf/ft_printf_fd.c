/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:53:14 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/10 12:52:39 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_printf_fd(int fd, const char *str)
{
	if (!str)
		return (-1);
	if (fd == STDOUT_FILENO)
		return (ft_printf("%s", str));
	write(fd, str, ft_strlen(str));
	return (ft_strlen(str));
}
