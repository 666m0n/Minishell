/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:30:19 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/13 15:56:01 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_simple(t_cmd *cmd, t_ctx *ctx)
{
	pid_t	pid;
	int		status;

	status = prepare_exec(cmd);
	if (status != SUCCESS)
		return (handle_command_error(cmd, status));
	pid = fork();
	if (pid == SYSCALL_ERROR)
		return (handle_system_error("fork"));
	if (pid == 0)
		exec_in_child(cmd, ctx);
	if (waitpid(pid, &status, 0) == -1)
		return (handle_system_error("waitpid"));
	return (WEXITSTATUS(status));
}

/*
** Execute une commande builtin sans redirection
** @param cmd: structure contenant la commande à exécuter
** @param ctx: contexte du shell
** @return: code de retour de la commande builtin ou ERROR si échec
*/
int	exec_builtin(t_cmd *cmd, t_ctx *ctx)
{
	builtin_func	builtin;
	const char		*cmd_name;
	int				status;

	cmd_name = get_cmd_name(cmd);
	if (!cmd_name)
		return (ERROR);
	builtin = get_builtin_function(cmd_name);
	if (!builtin)
		return (ERROR);
	if (has_redirection(cmd))
	{
		status = setup_redirections(cmd);
		if (status != SUCCESS)
			return (status);
		status = builtin(cmd, ctx);
		if (restore_fds(cmd) != SUCCESS)
			status = ERROR;
		return (status);
	}
	return (builtin(cmd, ctx));
}

/*
** Point d'entrée pour l'exécution d'une commande
** 1. Vérifie les heredocs et les traite si présents
** 2. Exécute la commande (builtin ou externe)
** @param cmd: structure contenant la commande à exécuter
** @param ctx: contexte du shell
** @return: code de retour de la commande, CMD_NOT_FOUND ou ERROR si échec
*/
int	execute_command(t_cmd *cmd, t_ctx *ctx)
{
	const char	*cmd_name;
	int			status;

	if (!cmd || !ctx)
		return (ERROR);
	// TO DO
	// Phase de prétraitement des heredocs
    // status = preprocess_heredocs(cmd);
    // if (status != SUCCESS)
    //   return (status);
	cmd_name = get_cmd_name(cmd);
	if (!cmd_name)
		return (CMD_NOT_FOUND);
	if (is_builtin(cmd_name) == TRUE)
		status = exec_builtin(cmd, ctx);
	else if (is_simple_command(cmd) == TRUE)
		status = exec_simple(cmd, ctx);
	else
		status = exec_pipe(cmd, ctx);
	set_exit_status(cmd, status);
	return (status);
}
