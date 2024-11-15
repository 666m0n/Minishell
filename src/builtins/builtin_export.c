/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:28:54 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/15 11:12:22 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Affiche une variable d'environnement au format export
** @param var: variable à afficher
** Format: declare -x nom="valeur" ou declare -x nom si pas de valeur
*/
static void	print_env_var(t_env *var)
{
	if (var->value != NULL)
		ft_printf("declare -x %s=\"%s\"\n", var->id, var->value);
	else
		ft_printf("declare -x %s\n", var->id);
}

/*
** Trouve la prochaine variable à afficher dans l'ordre alphabétique
** @param env: liste des variables
** @param printed: tableau de suivi des variables déjà affichées
** @param size: taille du tableau printed
** @return: prochaine variable ou NULL si toutes affichées
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
** Affiche toutes les variables d'environnement triées alphabétiquement
** @param ctx: contexte contenant l'environnement
** Limite: ne gère que 1024 variables maximum
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
** @param arg: chaîne au format "nom=valeur" ou "nom"
** @return: SUCCESS si mise à jour réussie, ERROR sinon
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
** Implémente la commande export
** Sans arg: affiche les variables triées
** Avec args: ajoute/met à jour chaque variable
** @param cmd: structure commande
** @param ctx: contexte shell
** @return: SUCCESS si ok, ERROR si au moins une erreur
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
