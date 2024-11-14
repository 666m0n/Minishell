/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:09:40 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/14 10:25:22 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**env_to_array(t_env *env)
{
	t_env	*current;
	char	**array;
	int		size;

	size = 0;
	current = env;
	while (current && ++size)
		current = current->next;
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	current = env;
	size = 0;
	while (current)
	{
		array[size++] = current->raw;
		current = current->next;
	}
	array[size] = NULL;
	return (array);
}

void	exec_in_child(t_cmd *cmd, t_ctx *ctx)
{
	char	**env_array;
	int		status;

	env_array = NULL;
	if (has_redirection(cmd))
	{
		status = setup_redirections(cmd);
		if (status != SUCCESS)
		{
			cleanup_fds(cmd);
			exit(status);
		}
	}
	env_array = env_to_array(ctx->envp);
	if (!env_array)
	{
		cleanup_fds(cmd);
		exit(MEMORY_ERROR);
    }
	execve(cmd->path, cmd->args, env_array);
	ft_free_array(env_array);
	cleanup_fds(cmd);
	exit(handle_system_error("execve"));
}

int prepare_exec(t_cmd *cmd)
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
	if (set_cmd_path(cmd, path) != SUCCESS)
	{
		free(path);
		return (ERROR);
	}
	free(path);
	return (SUCCESS);
}

