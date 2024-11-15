/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:09:21 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/15 11:15:34 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Vérifie si le nom de variable est valide selon POSIX
** @param var_name: nom à vérifier
** @return: TRUE si commence par lettre/_ et suivi de alphanum/_, FALSE sinon
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
** Libère la mémoire d'une variable d'environnement
** @param env: variable à libérer
** Note: ne libère que la structure, pas le suivant dans la liste
*/
void	env_del_one(t_env *env)
{
	if (!env)
		return ;
	if (env->raw)
		free(env->raw);
	free(env);
}

/*
** Supprime une variable de l'environnement
** @param ctx: contexte shell
** @param var_name: nom de la variable à supprimer
** @return: SUCCESS même si variable non trouvée
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
	i = 0;
	while (args[++i] != NULL)
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
	}
	return (status);
}

