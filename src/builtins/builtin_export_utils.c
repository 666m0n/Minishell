/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:05:03 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/12 19:10:49 by emmmarti         ###   ########.fr       */
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
t_env	*update_existing_var(t_env *var, const char *arg)
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
