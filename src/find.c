/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:22:44 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/13 15:30:50 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_command_path(const char *cmd_name)
{
	char	*path;
	char	**directories;
	char	*full_path;

	if (cmd_name == NULL)
		return (NULL);
	if (is_path(cmd_name)  == TRUE)
	{
		if (access(cmd_name, F_OK) == SYSCALL_SUCCESS)
			return (ft_strdup(cmd_name)); // ATTENTION -> FREE à faire dans une fonction appelante
		return (NULL);
	}
	path = getenv("PATH");
	if (path == NULL)
		path = DEFAULT_PATH;
	directories = ft_split(path, ':');
	if (directories == NULL)
		return (NULL);
	full_path = search_in_directory(directories, cmd_name);
	ft_free_array(directories);
	return (full_path); // ATTENTION -> FREE à faire dans une fonction appelante
}
