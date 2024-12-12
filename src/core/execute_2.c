/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:00:00 by emmmarti          #+#    #+#             */
/*   Updated: 2024/12/12 19:00:33 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Point d'entrée principal pour l'exécution des commandes
** @param cmd: commande à exécuter
** @param ctx: contexte du shell
** @return: code de sortie de la commande
** Note: détecte le type (builtin/simple/pipe) et redirige
** divise en 2 pour la gestion des signaux
*/
int	execute_command(t_cmd *cmd, t_ctx *ctx)
{
	const char	*cmd_name;
	int			status;

	if (!cmd || !ctx)
		return (ERROR);
	cmd_name = get_cmd_name(cmd);
	if (!cmd_name)
		ctx->exit_code = CMD_NOT_FOUND;
	status = process_heredocs(cmd);
	if (status != SUCCESS)
		return (status);
	status = execute_cmd_type(cmd, ctx, cmd_name);
	return (status);
}
