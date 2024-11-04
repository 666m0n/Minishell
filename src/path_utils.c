/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:39:53 by emmmarti          #+#    #+#             */
/*   Updated: 2024/11/04 10:32:01 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <dirent.h>

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

static t_bool	is_path(const char *cmd_name)
{
	if (!cmd_name)
		return (FALSE);
	if (cmd_name[0] == '/')
		return (TRUE);
	if (cmd_name[0] == '.' && cmd_name[1] == '/')
		return (TRUE);
	if (cmd_name[0] == '.' && cmd_name[1] == '.' && cmd_name[2] == '/')
		return (TRUE);
	return (FALSE);
}

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

t_bool	is_dir(const char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
		return (FALSE);
	closedir(dir);
	return (TRUE);
}

int	check_command(t_command *cmd)
{
	const char	*cmd_name;
	char 		*path;

	cmd_name = get_command_name(cmd);
	if (cmd_name == NULL)
		return (CMD_NOT_FOUND);
	if (is_dir(cmd_name) == TRUE)
		return (IS_DIR);
	path = find_command_path(cmd_name);
	if (path == NULL)
		return (CMD_NOT_FOUND);
	if (access(path, X_OK) == SYSCALL_ERROR)
	{
		free(path);
		return (PERMISSION_DENIED);
	}
	if (set_command_path(cmd, path) != SUCCESS)
	{
		free(path);
		return (ERROR);
	}
	return (SUCCESS);
}
