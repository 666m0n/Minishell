/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:21:31 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/14 12:00:30 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*search_in_directory(char **directories, const char *cmd)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	while (directories[i])
	{
		tmp = ft_strjoin(directories[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, F_OK) == SYSCALL_SUCCESS)
			return (full_path); // ATTENTION -> FREE à faire dans une fonction appelante
		free(full_path);
		i++;
	}
	return (NULL);
}

void ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_str_isdigit(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

