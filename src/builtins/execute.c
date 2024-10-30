/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:46:59 by emmmarti          #+#    #+#             */
/*   Updated: 2024/10/30 18:36:12 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	static const char	*builtins[] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int					i;

	if (!cmd)
		return (ERROR);
	i = 0;
	while (builtins[i])
	{
		if (!strcmp(cmd, builtins[i]))
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

int	execute_builtin(t_simple_cmd *cmd, t_ctx *ctx)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (builtin_echo(cmd));
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (builtin_cd(cmd));
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (builtin_pwd(cmd));
	if (!ft_strcmp(cmd->args[0], "export"))
		return (builtin_export(cmd));
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (builtin_unset(cmd));
	if (!ft_strcmp(cmd->args[0], "env"))
		return (builtin_env(cmd));
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (builtin_exit(cmd));
	return (ERROR);
}

int	execute_external_command(t_command *cmd, char **env)
{
	pid_t	pid;
	int		status;

	status = check_command(cmd, env);
	if (status != SUCCESS)
		return (status);
	pid = create_child_process();
	if (pid == 0)
		exec_in_child(cmd, env);
	else
		status = wait_child(pid);
	free(cmd->cmd->path);
	return (status);
}

int	execute_command(t_command *cmd, t_ctx *envp)
{
	if (!cmd || !cmd->cmd || !cmd->cmd->args || !cmd->cmd->args[0])
		return (CMD_NOT_FOUND);
	if (is_builtin(cmd->cmd->args[0]))
		cmd->exit_status = execute_builtin(cmd->cmd);
	else
		cmd->exit_status = execute_external_command(cmd->cmd, envp->envp);
	return (cmd->exit_status);
}
