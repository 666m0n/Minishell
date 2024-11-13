/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:19:47 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/13 14:21:21 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_redirections(t_cmd *cmd)
{
	int	status;

	if	(cmd->fd->curr_in)
	{
		status = apply_input_redirection(cmd);
		if (status != SUCCESS)
			return (status);
	}
	if (cmd->fd->curr_out)
	{
		status = apply_output_redirection(cmd);
		if (status != SUCCESS)
			return (status);
	}
	return (SUCCESS);
}

void	find_final_redirections(t_cmd *cmd)
{
	t_redirection	*current;

	cmd->fd->curr_in = NULL;
	cmd->fd->curr_out = NULL;
	current = cmd->redirections;
	while (current)
	{
		if (current->type == REDIR_IN || current->type == HEREDOC)
			cmd->fd->curr_in = current;
		else if (current->type == REDIR_OUT || current->type == APPEND)
			cmd->fd->curr_out = current;
		current = current->next;
	}
}

/*
** Restaure les descripteurs de fichiers standard
*/
int	restore_fds(t_cmd *cmd)
{
	if (dup2(cmd->fd->stdin_backup, STDIN_FILENO) == SYSCALL_ERROR)
		return (handle_system_error("dup2"));
	if (dup2(cmd->fd->stdout_backup, STDOUT_FILENO) == SYSCALL_ERROR)
		return (handle_system_error("dup2"));
	close(cmd->fd->stdin_backup);
	close(cmd->fd->stdout_backup);
	return (SUCCESS);
}

int	save_fd(t_cmd *cmd)
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
	cmd->fd->stdin_backup = fd_in;
	cmd->fd->stdout_backup = fd_out;
	return (SUCCESS);
}

int	setup_redirections(t_cmd *cmd)
{
	int				status;

	status = save_fd(cmd);
	if (status != SUCCESS)
		return (status);
	find_final_redirections(cmd);
	status = handle_redirections(cmd);
	if (status != SUCCESS)
	{
		cleanup_fds(cmd);
		return (status);
	}
	return (SUCCESS);
}
