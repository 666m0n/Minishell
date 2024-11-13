/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:19:01 by emmmarti          #+#    #+#             */
/*   Updated: 2024/11/13 15:24:04 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	is_path(const char *cmd_name)
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

t_bool	is_dir(const char *path)
{
	DIR	*dir;

	if (!path || !*path)
		return (FALSE);
	dir = opendir(path);
	if (!dir)
		return (FALSE);
	closedir(dir);
	return (TRUE);
}

t_bool	is_builtin(const char *cmd_name)
{
	int					i;
	static const char	*builtins[] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(cmd_name, builtins[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	is_simple_command(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (FALSE);
	if (cmd->next == NULL)
		return (TRUE);
	else
		return (FALSE);
}
