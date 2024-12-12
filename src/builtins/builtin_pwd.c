/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:03:33 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/12 12:10:43 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Implémente la commande pwd
** Affiche le chemin absolu du répertoire de travail actuel
** @param cmd: structure commande
** @param ctx: contexte shell (non utilisé)
** @return: SUCCESS si ok, ERROR si échec (droits, etc.)
*/
int	builtin_pwd(t_cmd *cmd, t_ctx *ctx)
{
	char	*current_path;

	(void)ctx;
	if (!cmd || !cmd->args)
		return (ERROR);
	current_path = getcwd(NULL, 0);
	if (current_path == NULL)
		return (handle_builtin_error("pwd", NULL, strerror(errno)));
	ft_printf("%s\n", current_path);
	free(current_path);
	return (SUCCESS);
}
