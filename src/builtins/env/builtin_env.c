/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:26:26 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/17 15:27:48 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Implémente la commande env sans options ni arguments
** Affiche uniquement les variables qui ont une valeur assignée
** @param cmd: structure contenant la commande et ses arguments
** @param ctx: contexte contenant l'environnement
** @return: SUCCESS si pas d'argument, ERROR sinon
*/
int	builtin_env(t_cmd *cmd, t_ctx *ctx)
{
	t_env	*current;

	if (!is_valid_command(cmd))
		return (ERROR);
	if (cmd->args[1])
		return (handle_builtin_error("env", NULL, "too many arguments"));
	current = ctx->envp;
	while (current)
	{
		if (current->value)
			ft_printf("%s=%s\n", current->id, current->value);
		current = current->next;
	}
	return (SUCCESS);
}
