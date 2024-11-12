/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:19:47 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/12 14:44:46 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_final_redirections(t_cmd *cmd, t_redirection **last_in, \
							t_redirection **last_out)
{
	t_redirection	*current;

	if (!cmd || !last_in || !last_out)
		return (ERROR);
	*last_in = NULL;
	*last_out = NULL;
	current = cmd->redirections;
	if (!current)
		return (ERROR);
	while (current)
	{
		if (current->type == REDIR_IN || current->type == HEREDOC)
			*last_in == current;
		else if (current->type == REDIR_OUT || current->type == APPEND)
			*last_out == current;
		current = current->next;
	}
	return (SUCCESS);
}

static int	save_fd(t_cmd *cmd)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	if (fd_in == SYSCALL_ERROR)
		return (handle_system_error("dup"));
	fd_out = dup(STDOUT_FILENO);
	if (fd_out == SYSCALL_ERROR)
	{
		close(fd_in);
		return (handle_system_error("dup"));
	}
	cmd->stdin_backup = fd_in;
	cmd->stdout_backup = fd_out;
	return (SUCCESS);
}

int	exec_builtin_redir(t_cmd *cmd, t_ctx *ctx)
{
	int	status;
	int	last_in;
	int	last_out;

	if (!cmd || !ctx)
		return (ERROR);
	status = save_fd(cmd);
	if (status == ERROR)
		return (status);
	status = find_final_redirections(cmd, &last_in, &last_out);
	if (status == ERROR)
		return (status);
	return (SUCCESS);
}
