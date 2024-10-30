/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:39:53 by emmmarti          #+#    #+#             */
/*   Updated: 2024/10/30 18:27:13 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
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
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(const char *cmd)
{
	char	*path_env;
	char	**directories;
	char	*full_path;


	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return (ft_strdup(cmd));
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	directories = ft_split(path_env, ':');
	if (directories == NULL)
		return (NULL);
	full_path = search_in_directory(directories, cmd);
	free_array(directories);
	return (full_path);
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

int	check_command(t_command *cmd, char **env)
{
	if (is_dir(cmd->cmd->args[0]))
		return (IS_DIR);
	cmd->cmd->path = find_command_path(cmd->cmd->args[0]);
	if (!cmd->cmd->path)
		return (CMD_NOT_FOUND);
	if (access(cmd->cmd->path, X_OK) == -1)
		return (PERMISSION_DENIED);
	return (SUCCESS);
}
