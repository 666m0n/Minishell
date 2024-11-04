/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:46:59 by emmmarti          #+#    #+#             */
/*   Updated: 2024/11/04 10:29:29 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	is_builtin(const char *cmd_name)
{
	static const char	*builtins[] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int					i;

	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(cmd_name, builtins[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int execute_builtin(t_command *cmd, t_ctx *ctx)
{
	const char		*cmd_name;
	builtin_func	func;
	int				status;

	cmd_name = get_command_name(cmd);
	if (cmd_name == NULL)
		return (CMD_NOT_FOUND);
	func = get_builtin_function(cmd_name);
	if (func)
	{
		status = func(cmd, ctx);
		return (status);
	}
	return (ERROR);
}

int	execute_external_command(t_command *cmd, t_ctx *ctx)
{
	pid_t	pid;
	int		status;
	char 	*path;

	status = check_command(cmd);
	if (status != SUCCESS)
		return (handle_command_error(cmd, status));
	pid = create_child_process();
	if (pid == SYSCALL_ERROR)
	{
		ft_printf("minishell: fork: %s\n", strerror(errno));
		return (ERROR);
    }
	else if (pid == SYSCALL_SUCCESS)
        exec_in_child(cmd, ctx);
	else
		status = wait_child(pid);
	path = get_command_path(cmd);
	if (path != NULL)
		free(path);
	return (status);
}

int	execute_command(t_command *cmd, t_ctx *ctx)
{
	const char	*cmd_name;
	int			exit_status;

	if (ctx == NULL)
        return (ERROR);
	cmd_name = get_command_name(cmd);
	if (cmd_name == NULL)
		return (CMD_NOT_FOUND);
	if (is_builtin(cmd_name) == TRUE)
		exit_status = execute_builtin(cmd, ctx);
	else
		exit_status = execute_external_command(cmd, ctx);
	set_exit_status(cmd, exit_status);
	return (exit_status);
}
