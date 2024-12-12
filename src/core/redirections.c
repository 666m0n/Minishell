/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:19:47 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/12 19:06:02 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Applique les redirections d'entrée et sortie actives
** @param cmd: structure de commande
** @return: SUCCESS si ok, code d'erreur si échec
** Note: vérifie curr_in et curr_out avant d'appliquer
*/
int	handle_redirections(t_cmd *cmd)
{
	int	status;

	if (cmd->fd->curr_in > 0)
	{
		status = apply_input_redirection(cmd);
		if (status != SUCCESS)
			return (status);
	}
	if (cmd->fd->curr_out > 0)
	{
		status = apply_output_redirection(cmd);
		if (status != SUCCESS)
			return (status);
	}
	return (SUCCESS);
}

/*
** Identifie les dernières redirections d'entrée et sortie dans la liste
** @param cmd: structure de commande
*/
void	find_final_redirections(t_cmd *cmd)
{
	t_redirection	*current;

	initialize_fd(cmd->fd);
	current = cmd->redirections;
	while (current)
	{
		if (current->type == T_REDIRIN || current->type == T_HEREDOC)
			handle_input_redirection(cmd->fd, current);
		else if (current->type == T_REDIROUT || current->type == T_APPEND)
			handle_output_redirection(cmd->fd, current);
		current = current->next;
	}
}

/*
** Restaure les descripteurs stdin/stdout sauvegardés
** @param cmd: structure de commande
** @return: SUCCESS si ok, ERROR si échec de dup2
*/
int	restore_fds(t_cmd *cmd)
{
	if (dup2(cmd->fd->stdin_backup, STDIN_FILENO) == SYSCALL_ERROR)
	{
		close(cmd->fd->stdin_backup);
		return (handle_system_error("dup2"));
	}
	if (dup2(cmd->fd->stdout_backup, STDOUT_FILENO) == SYSCALL_ERROR)
	{
		close(cmd->fd->stdout_backup);
		return (handle_system_error("dup2"));
	}
	close(cmd->fd->stdin_backup);
	close(cmd->fd->stdout_backup);
	return (SUCCESS);
}

/*
** Sauvegarde les descripteurs stdin/stdout actuels
** @param cmd: structure de commande
** @return: SUCCESS si ok, ERROR si échec de dup
*/
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

/*
** Configure toutes les redirections pour une commande
** - Sauvegarde les FDs originaux
** - Trouve les redirections finales
** - Applique les redirections
** @param cmd: structure de commande
** @return: SUCCESS si ok, code d'erreur sinon
*/
int	setup_redirections(t_cmd *cmd)
{
	int	status;

	if (!cmd->fd)
		return (ERROR);
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
