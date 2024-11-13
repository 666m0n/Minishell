/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:28:54 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/13 09:50:38 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Affiche une seule variable d'environnement au format export
** @param var: variable d'environnement à afficher
*/
static void	print_env_var(t_env *var)
{
	if (var->value != NULL)
		ft_printf("declare -x %s=\"%s\"\n", var->id, var->value);
	else
		ft_printf("declare -x %s\n", var->id);
}

/*
** Trouve la prochaine variable d'environnement à afficher dans l'ordre
** @param env: liste des variables d'environnement
** @param printed: tableau des variables déjà affichées
** @param size: taille du tableau printed
** @return: variable suivante ou NULL si toutes ont été affichées
*/
static t_env	*find_next_var(t_env *env, t_bool *printed, int size)
{
	int		i;
	t_env	*min;

	i = 0;
	min = NULL;
	while (i < size)
	{
		if (printed[i] == FALSE)
			min = find_min_var(env, min ? min->id : NULL);
		i++;
	}
	return (min);
}

/*
** Affiche toutes les variables d'environnement triées
** @param ctx: contexte contenant l'environnement
*/
static void	display_sorted_env(t_ctx *ctx)
{
	t_env	*current;
	t_bool	printed[1024];
	int		env_size;
	int		i;

	env_size = 0;
	current = ctx->envp;
	while (current != NULL)
	{
		env_size++;
		current = current->next;
	}
	if (env_size > 1024)
		return ;
	ft_memset(printed, FALSE, sizeof(t_bool) * env_size);
	i = -1;
	while (++i < env_size)
	{
		current = find_next_var(ctx->envp, printed, env_size);
		if (current != NULL)
		{
			print_env_var(current);
			printed[i] = TRUE;
		}
	}
}

/*
** Met à jour ou ajoute une variable d'environnement
** @param ctx: contexte contenant l'environnement
** @param arg: chaîne au format "name=value" ou "name"
** @return: SUCCESS en cas de succès, ERROR sinon
*/
static int	update_env_variable(t_ctx *ctx, const char *arg)
{
	char	*name;
	char	*value;
	t_env	*existing;
	t_env	*new_var;

	if (extract_name_value(arg, &name, &value) == ERROR)
		return (ERROR);
	if (is_valid_identifier(name) == FALSE)
	{
		ft_printf("export: '%s': not a valid identifier\n", arg);
		free(name);
		free(value);
		return (ERROR);
	}
	existing = find_existing_var(ctx->envp, name);
	if (existing != NULL)
		return (update_existing_var(existing, name, value));
	new_var = create_env_var(name, value);
	if (new_var == NULL)
		return (ERROR);
	new_var->next = ctx->envp;
	ctx->envp = new_var;
	return (SUCCESS);
}

/*
** Implémente la commande builtin export de bash
** @param cmd: structure contenant la commande et ses arguments
** @param ctx: contexte d'exécution
** @return: SUCCESS en cas de succès, ERROR en cas d'erreur
*/
int builtin_export(t_cmd *cmd, t_ctx *ctx)
{
	char	**args;
	int		i;
	int		status;

	if (!cmd || !cmd->args)
		return (ERROR);
	args = cmd->args;
	if (args[1] == NULL)
	{
		display_sorted_env(ctx);
		return (SUCCESS);
	}
	status = SUCCESS;
	i = 1;
	while (args[i] != NULL)
	{
		if (update_env_variable(ctx, args[i]) == ERROR)
			status = ERROR;
		i++;
	}
	return (status);
}
