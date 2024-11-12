/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:30:19 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/11 16:17:27 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Point d'entrée pour l'exécution d'une commande
** 1. Vérifie les heredocs et les traite si présents
** 2. Exécute la commande (builtin ou externe)
** @param cmd: structure contenant la commande à exécuter
** @param ctx: contexte du shell
** @return: code de retour de la commande, CMD_NOT_FOUND ou ERROR si échec
*/
int	execute_command(t_command *cmd, t_ctx *ctx)
{
	const char	*cmd_name;
	int			status;

	if (!ctx)
		return (ERROR);
	cmd_name = get_command_name(cmd);
	if (!cmd_name)
		return (CMD_NOT_FOUND);
	if (is_builtin(cmd_name) == TRUE)
	{
		if (has_redirection(cmd))
			status = exec_builtin_redir(cmd, ctx);
		else
			status = exec_builtin(cmd, ctx);
	}
	else
	{
		if (is_simple_command(cmd))
			status = exec_simple(cmd);
		else
			status = exec_pipe(cmd, ctx);
	}
	set_exit_status(cmd, status);
	return (status);
}
