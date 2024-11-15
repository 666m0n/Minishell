/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:26:26 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/15 11:04:05 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Implémente la commande env
** Affiche les variables d'environnement selon les règles suivantes :
** - N'accepte aucun argument ou option
** - Affiche uniquement les variables qui ont une valeur assignée
** - Format d'affichage : "nom=valeur"
** @param cmd: structure contenant la commande et ses arguments
** @param ctx: contexte contenant l'environnement
** @return: SUCCESS si pas d'argument, ERROR sinon
*/
int	builtin_env(t_cmd *cmd, t_ctx *ctx)
{
	t_env	*current;

	if (!cmd || !cmd->args)
		return (ERROR);
	if (cmd->args[1] != NULL)
		return (handle_builtin_error("env", NULL, "too many arguments"));
	current = ctx->envp;
	while (current != NULL)
	{
		if (current->value != NULL)
			ft_printf("%s=%s\n", current->id, current->value);
		current = current->next;
	}
	return (SUCCESS);
}

