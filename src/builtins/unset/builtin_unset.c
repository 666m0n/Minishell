/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:09:21 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/17 15:28:24 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Supprime une variable de l'environnement
** @param ctx: contexte shell
** @param var_name: nom de la variable à supprimer
** @return: SUCCESS ou ERROR si échec système
*/
static int	remove_env_var(t_ctx *ctx, const char *var_name)
{
	t_env	*current;
	t_env	*prev;

	current = ctx->envp;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->id, var_name) == 0)
		{
			if (prev == NULL)
				ctx->envp = current->next;
			else
				prev->next = current->next;
			free(current->raw);
			free(current->id);
			if (current->value)
				free(current->value);
			free(current);
			return (SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (SUCCESS);
}

/*
** Implémente la commande unset
** Supprime chaque variable listée en argument si son nom est valide
** @param cmd: structure commande
** @param ctx: contexte shell
** @return: SUCCESS si tout ok, ERROR si un nom invalide
*/
int	builtin_unset(t_cmd *cmd, t_ctx *ctx)
{
	char	**args;
	int		status;
	int		i;

	if (!cmd || !cmd->args)
		return (ERROR);
	args = cmd->args;
	if (args[1] == NULL)
		return (SUCCESS);
	status = SUCCESS;
	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]) == FALSE)
		{
			handle_builtin_error("unset", args[i], "not a valid identifier");
			status = ERROR;
		}
		else if (remove_env_var(ctx, args[i]) == ERROR)
			status = ERROR;
		i++;
	}
	return (status);
}
