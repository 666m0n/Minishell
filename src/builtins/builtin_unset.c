/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:09:21 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/03 18:51:24 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Vérifie si le nom de la variable est valide selon les règles POSIX
** @param var_name: nom de la variable à vérifier
** @return: TRUE si le nom est valide, FALSE sinon
*/
static t_bool	is_valid_var_name(const char *var_name)
{
	int	i;

	if (var_name == NULL || var_name[0] == '\0')
		return (FALSE);
	if (ft_isalpha(var_name[0]) == FALSE && var_name[0] != '_')
		return (FALSE);
	i = 1;
	while (var_name[i] != '\0')
	{
		if (ft_isalnum(var_name[i]) == FALSE && var_name[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
** Supprime une variable de l'environnement
** @param ctx: contexte contenant l'environnement
** @param var_name: nom de la variable à supprimer
** @return: SUCCESS dans tous les cas (même si la variable n'existe pas)
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
			env_del_one(current);
			return (SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (SUCCESS);
}

/*
** Implémente la commande builtin unset de bash
** @param cmd: structure contenant la commande et ses arguments
** @param ctx: contexte d'exécution
** @return: SUCCESS si la variable est supprimée ou n'existe pas,
**          ERROR   si le nom de la variable est invalide.
*/
int	builtin_unset(t_command *cmd, t_ctx *ctx)
{
	char	**args;
	int		status;
	int		i;

	if (cmd == NULL || cmd->cmd == NULL || cmd->cmd->args == NULL)
		return (ERROR);
	args = cmd->cmd->args;
	if (args[1] == NULL)
		return (SUCCESS);
	status = SUCCESS;
	i = 1;
	while (args[i] != NULL)
	{
		if (is_valid_var_name(args[i]) == FALSE)
		{
			handle_builtin_error("unset", args[i], "not a valid identifier");
			status = ERROR;
		}
		else
		{
			if (remove_env_var(ctx, args[i]) == ERROR)
				status = ERROR;
		}
		i++;
	}
	return (status);
}
