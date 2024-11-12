/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:26:38 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/12 14:09:27 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

const char	*get_cmd_name(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (NULL);
	return (cmd->args[0]);
}

int	get_exit_status(t_cmd *cmd)
{
	if (!cmd)
		return (ERROR);
	return (cmd->exit_status);
}

char	*get_cmd_path(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	return (cmd->path);
}

builtin_func	get_builtin_function(const char *cmd_name)
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
