/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:38:56 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/10 14:39:46 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Sauvegarde les descripteurs de fichiers standards
** @param cmd: commande simple contenant les FDs à sauvegarder
** @return: SUCCESS ou ERROR
*/
static int	backup_fds(t_simple_cmd *cmd)
{
	cmd->input.backup = dup(STDIN_FILENO);
	if (cmd->input.backup == SYSCALL_ERROR)
		return (ERROR);
	cmd->output.backup = dup(STDOUT_FILENO);
	if (cmd->output.backup == SYSCALL_ERROR)
	{
		close(cmd->input.backup);
		return (ERROR);
	}
	return (SUCCESS);
}

/*
** Restaure les descripteurs de fichiers standards
** @param cmd: commande simple contenant les FDs à restaurer
*/
static void	restore_fds(t_simple_cmd *cmd)
{
	if (cmd->input.backup != -1)
	{
		dup2(cmd->input.backup, STDIN_FILENO);
		close(cmd->input.backup);
	}
	if (cmd->output.backup != -1)
	{
		dup2(cmd->output.backup, STDOUT_FILENO);
		close(cmd->output.backup);
	}
}

/*
** Configure les redirections pour le builtin
** @param cmd: commande simple à configurer
** @return: SUCCESS ou ERROR
*/
static int	setup_redirections(t_simple_cmd *cmd)
{
	if (cmd->input.current != -1)
	{
		if (dup2(cmd->input.current, STDIN_FILENO) == SYSCALL_ERROR)
			return (ERROR);
	}
	if (cmd->output.current != -1)
	{
		if (dup2(cmd->output.current, STDOUT_FILENO) == SYSCALL_ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

/*
** Exécute un builtin avec gestion des redirections et heredocs
** @param cmd: structure de commande contenant le builtin
** @param ctx: contexte du shell
** @return: code de retour du builtin ou ERROR si échec
*/
int	execute_builtin(t_command *cmd, t_ctx *ctx)
{
	builtin_func	builtin;
	const char		*cmd_name;
	int				status;

	cmd_name = get_command_name(cmd);
	if (!cmd_name)
		return (ERROR);
	builtin = get_builtin_function(cmd_name);
	if (!builtin)
		return (ERROR);
	if (backup_fds(cmd->cmd) == ERROR)
		return (ERROR);
	if (setup_redirections(cmd->cmd) == ERROR)
	{
		restore_fds(cmd->cmd);
		return (ERROR);
	}
	status = builtin(cmd, ctx);
	restore_fds(cmd->cmd);
	return (status);
}
