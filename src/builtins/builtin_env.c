/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:26:26 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/13 09:48:21 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Implémente la commande builtin env de bash
** @param cmd: structure contenant la commande et ses arguments
** @param ctx: contexte d'exécution contenant l'environnement
** @return: SUCCESS en cas de succès, ERROR en cas d'erreur
** N'accepte aucune option ni argument
** Affiche les variables d'environnement selon les règles suivantes:
** - Affiche les variables avec une valeur (même vide): "nom=valeur"
** - Affiche les variables avec une valeur vide: "nom="
** - N'affiche pas les variables sans valeur assignée
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

