/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:05:03 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/12 12:07:10 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Trouve une variable dans l'environnement par son nom
** @param env: liste des variables d'environnement
** @param name: nom de la variable à chercher (peut inclure '=value')
** @return: pointeur vers la variable si trouvée, NULL sinon
** Note: compare jusqu'au '=' s'il existe dans name
*/
t_env	*find_existing_var(t_env *env, const char *name)
{
	t_env	*current;
	int		len;

	if (!name || (name[0] == '_' && name[1] == '\0'))
		return (NULL);
	len = 0;
	while (name[len] && name[len] != '=')
		len++;
	current = env;
	while (current)
	{
		if (current->id && !ft_strncmp(current->id, name, len)
			&& !current->id[len])
			return (current);
		current = current->next;
	}
	return (NULL);
}

/*
** Initialise les champs d'une variable d'environnement
** @param new: structure à initialiser
** @param equals: pointeur vers le '=' trouvé dans la chaîne
** Note: sépare la chaîne en id/value au niveau du '=' si présent
*/
static void	init_var_values(t_env *new, char *equals)
{
	if (equals)
	{
		*equals = '\0';
		new->id = new->raw;
		new->value = equals + 1;
	}
	else
	{
		new->id = new->raw;
		new->value = NULL;
	}
	new->next = NULL;
}

/*
** Crée une nouvelle variable d'environnement
** @param arg: chaîne complète (nom=valeur ou nom)
** @param value: valeur déjà extraite (peut être NULL)
** @return: nouvelle variable allouée, NULL si erreur
** Note: alloue et initialise une nouvelle structure t_env
*/
t_env	*create_var(const char *arg, char *value)
{
	t_env	*new;
	char	*equals;

	(void)value;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->raw = ft_strdup(arg);
	if (!new->raw)
	{
		free(new);
		return (NULL);
	}
	equals = ft_strchr(new->raw, '=');
	init_var_values(new, equals);
	return (new);
}

/*
** Extrait la valeur après le signe égal
** @param arg: chaîne au format "nom=valeur"
** @return: valeur allouée ou NULL si pas de '='
** Note: retourne une chaîne vide si rien après le '='
*/
char	*extract_value(const char *arg)
{
	char	*eq;
	char	*tmp;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (NULL);
	tmp = ft_strdup(eq + 1);
	return (tmp);
}

/*
** Met à jour une variable d'environnement existante
** @param var: variable à mettre à jour
** @param arg: nouvel argument (VAR=value)
** @return: pointeur sur la variable mise à jour, NULL si erreur
*/
static t_env	*update_existing_var(t_env *var, const char *arg)
{
	char	*equals;

	free(var->raw);
	var->raw = ft_strdup(arg);
	if (!var->raw)
		return (NULL);
	equals = strchr(var->raw, '=');
	if (equals)
	{
		*equals = '\0';
		var->id = var->raw;
		var->value = equals + 1;
	}
	return (var);
}

/*
** Met à jour ou crée une variable d'environnement
** @param ctx: contexte du shell
** @param arg: argument complet (VAR=value ou VAR)
** @return: pointeur sur la variable mise à jour/créée, NULL si erreur
*/
t_env	*update_env_variable(t_ctx *ctx, const char *arg)
{
	t_env	*var;
	char	*value;

	value = extract_value(arg);
	var = find_existing_var(ctx->envp, arg);
	if (var)
		var = update_existing_var(var, arg);
	else
	{
		var = create_var(arg, value);
		if (!var)
			return (NULL);
		var->next = ctx->envp;
		ctx->envp = var;
	}
	if (value)
		free(value);
	return (var);
}

/*
** Vérifie si une chaîne est un identifiant valide pour une variable
** - Doit commencer par une lettre ou underscore
** - Ne peut contenir que lettres, chiffres, underscores
** - S'arrête au premier '=' si présent
** @param str: chaîne à vérifier
** @return: TRUE si valide, FALSE sinon
*/
int	is_valid_identifier(const char *str)
{
	if (!str || !*str)
		return (FALSE);
	if (!ft_isalpha(*str) && *str != '_')
		return (FALSE);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (FALSE);
		str++;
	}

	return (TRUE);
}

/*
** Libère tous les composants d'une variable d'environnement
** @param var: variable d'environnement à libérer
** Note: libère raw, id, value et la structure elle-même
** Note: gère le cas où var est NULL ou certains composants sont NULL
*/
void	free_env_var(t_env *var)
{
	if (!var)
		return ;
	if (var->raw)
		free(var->raw);
	if (var->id)
		free(var->id);
	if (var->value)
		free(var->value);
	free(var);
}
