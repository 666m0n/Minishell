/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:08:15 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/14 10:27:01 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	apply_input_redirection(t_cmd *cmd)
{
	int		new_fd;
	t_token	type;
	char	*file;

	type = cmd->redirections->type;
	file = cmd->redirections->file;
	if (type == HEREDOC)
		return (setup_heredoc(cmd, cmd->redirections));
	new_fd = open(file, O_RDONLY);
	if (new_fd == SYSCALL_ERROR)
		return (handle_system_error("open"));
	if (dup2(new_fd, STDIN_FILENO) == SYSCALL_ERROR)
	{
		close(new_fd);
		return (handle_system_error("dup2"));
	}
	close(new_fd);
	return (SUCCESS);
}

int	apply_output_redirection(t_cmd *cmd)
{
	int		new_fd;
	int		flags;
	t_token	type;
	char	*file;

	type = cmd->redirections->type;
	file = cmd->redirections->file;
	if (type == REDIR_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	new_fd = open(file, flags, 0644);
	if (new_fd == SYSCALL_ERROR)
		return (handle_system_error("open"));
	if (dup2(new_fd, STDOUT_FILENO) == SYSCALL_ERROR)
	{
		close(new_fd);
		return (handle_system_error("dup2"));
	}
	close(new_fd);
	return (SUCCESS);
}
