/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:28:37 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/13 01:19:50 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_special_path(const char *path)
{
	if (!path || !*path)
		return (FALSE);
	if (ft_strcmp(path, ".") == 0 || ft_strcmp(path, "..") == 0)
		return (TRUE);
	if (ft_strncmp(path, "./", 2) == 0 || ft_strncmp(path, "../", 3) == 0)
		return (TRUE);
	return (FALSE);
}

char	*get_current_dir(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	return (cwd);
}

int	update_pwd_vars(t_ctx *ctx, char *old_pwd)
{
	char	*current;
	char	*pwd_str;
	char	*oldpwd_str;

	current = get_current_dir();
	if (!current)
		return (ERROR);
	pwd_str = ft_strjoin("PWD=", current);
	if (!pwd_str)
		return (free(current), ERROR);
	if (old_pwd)
		oldpwd_str = ft_strjoin("OLDPWD=", old_pwd);
	else
		oldpwd_str = ft_strdup("OLDPWD=");
	if (!oldpwd_str)
		return (free(current), free(pwd_str), ERROR);
	update_env_variable(ctx, pwd_str);
	update_env_variable(ctx, oldpwd_str);
	free(current);
	free(pwd_str);
	free(oldpwd_str);
	return (SUCCESS);
}

char	*get_home_directory(t_ctx *ctx)
{
	char	*home;

	home = get_env_value(ctx->envp, "HOME");
	if (!home)
		return (handle_builtin_error("cd", NULL, "HOME not set"), NULL);
	return (ft_strdup(home));
}

int	check_directory_access(const char *path)
{
	if (access(path, F_OK) == SYSCALL_ERROR)
		return (handle_builtin_error("cd", path, "No such file or directory"));
	if (!is_dir(path) && !is_special_path(path))
		return (handle_builtin_error("cd", path, "Not a directory"));
	if (access(path, R_OK) == SYSCALL_ERROR)
		return (handle_builtin_error("cd", path, "Permission denied"));
	return (SUCCESS);
}

