/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:26:38 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/04 10:19:51 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

const	char *get_command_name(t_command *cmd)
{
	if (!cmd || !cmd->cmd || !cmd->cmd->args || !cmd->cmd->args[0])
		return (NULL);
	return (cmd->cmd->args[0]);
}

int	get_exit_status(t_command *cmd)
{
	if (!cmd)
		return (ERROR);
	return (cmd->exit_status);
}

char *get_command_path(t_command *cmd)
{
	if (!cmd || !cmd->cmd)
		return (NULL);
	return (cmd->cmd->path);
}

builtin_func get_builtin_function(const char *cmd_name)
{
	if (!ft_strcmp(cmd_name, "echo"))
		return (builtin_echo);
	else if (!ft_strcmp(cmd_name, "cd"))
		return (builtin_cd);
	else if (!ft_strcmp(cmd_name, "pwd"))
		return (builtin_pwd);
	else if (!ft_strcmp(cmd_name, "export"))
		return (builtin_export);
	else if (!ft_strcmp(cmd_name, "unset"))
		return (builtin_unset);
	else if (!ft_strcmp(cmd_name, "env"))
		return (builtin_env);
	else if (!ft_strcmp(cmd_name, "exit"))
		return (builtin_exit);
	return (NULL);
}
