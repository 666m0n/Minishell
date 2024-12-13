/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:15:16 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/13 01:17:56 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_directory(const char *path, t_ctx *ctx)
	{
	char	*old_pwd;
	int		status;

	if (!path)
		return (ERROR);
	old_pwd = get_current_dir();
	if (!old_pwd)
		return (handle_system_error("getcwd"));
	status = check_directory_access(path);
	if (status != SUCCESS)
	{
		free(old_pwd);
		return (status);
	}
	if (chdir(path) == SYSCALL_ERROR)
	{
		free(old_pwd);
		return (handle_builtin_error("cd", NULL, strerror(errno)));
	}
	status = update_pwd_vars(ctx, old_pwd);
	free(old_pwd);
	return (status);
}

int	builtin_cd(t_cmd *cmd, t_ctx *ctx)
{
	char	*path;
	char	**args;

	if (!cmd || !cmd->args)
		return (ERROR);
	args = cmd->args;
	if (args[1] == NULL || !ft_strcmp(args[1], "~"))
	{
		path = get_home_directory(ctx);
		if (!path)
			return (ERROR);
		if (change_directory(path, ctx) != SUCCESS)
			return (free(path), ERROR);
		return (free(path), SUCCESS);
	}
	if (args[2] != NULL)
		return (handle_builtin_error("cd", NULL, "too many arguments"));
	return (change_directory(args[1], ctx));
}
