/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:21:31 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/12 15:30:41 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	ft_str_isdigit(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	free_tab_partial(char **tab, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	execute_cmd_type(t_cmd *cmd, t_ctx *ctx, const char *cmd_name)
{
	int	status;

	if (is_simple_command(cmd) == FALSE)
		status = exec_pipe(cmd);
	else if (is_builtin(cmd_name) == TRUE)
		status = exec_builtin(cmd, ctx, FALSE);
	else
		status = exec_simple(cmd, ctx);
	set_exit_status(cmd, status);
	ctx->exit_code = status;
	cleanup_heredoc_files(cmd);
	return (status);
}
