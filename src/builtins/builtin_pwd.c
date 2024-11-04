/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:03:33 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/04 10:07:32 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Gère l'affichage du chemin absolu du répertoire de travail actuel
** @param cmd: structure contenant la commande et ses arguments
** @param ctx: contexte d'exécution
** @return: SUCCESS en cas de succès, ERROR en cas d'erreur
*/
int	builtin_pwd(t_command *cmd, t_ctx *ctx)
{
	char	*current_path;
	char	**args;

	(void)ctx;
	if (cmd == NULL || cmd->cmd == NULL || cmd->cmd->args == NULL)
		return (ERROR);
	args = cmd->cmd->args;
	if (args[1] != NULL)
		 return (handle_builtin_error("pwd", NULL, "too many arguments"));
	current_path = getcwd(NULL, 0);
	if (current_path == NULL)
		return (handle_builtin_error("pwd", NULL, strerror(errno)));
	ft_printf("%s\n", current_path);
	free(current_path);
	return (SUCCESS);
}
