/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:05:03 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/04 10:15:25 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Vérifie si le premier caractère du nom de variable est valide
** @param c: caractère à vérifier
** @return: TRUE si valide, FALSE sinon
*/
t_bool	is_valid_first_char(char c)
{
	if (c == '\0' || ft_isdigit(c) == TRUE)
		return (FALSE);
	if (c != '_' && ft_isalpha(c) == FALSE)
		return (FALSE);
	return (TRUE);
}

/*
** Vérifie si le nom de la variable est valide selon les règles POSIX
** @param var_name: nom de la variable à vérifier
** @return: TRUE si le nom est valide, FALSE sinon
*/
t_bool	is_valid_identifier(const char *var_name)
{
	int	i;

	if (var_name == NULL || is_valid_first_char(var_name[0]) == FALSE)
		return (FALSE);
	i = 1;
	while (var_name[i] != '\0' && var_name[i] != '=')
	{
		if (var_name[i] != '_' && ft_isalnum(var_name[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
** Extrait le nom et la valeur d'une variable d'environnement
** @param arg: chaîne d'entrée (format: "name=value" ou "name")
** @param name: pointeur vers le nom extrait
** @param value: pointeur vers la valeur extraite
** @return: SUCCESS si l'extraction réussit, ERROR sinon
*/
int	extract_name_value(const char *arg, char **name, char **value)
{
	char	*equals_pos;

	equals_pos = ft_strchr(arg, '=');
	if (equals_pos != NULL)
	{
		*name = ft_strndup(arg, equals_pos - arg);
		*value = ft_strdup(equals_pos + 1);
		if (*name == NULL || *value == NULL)
			return (ERROR);
	}
	else
	{
		*name = ft_strdup(arg);
		*value = NULL;
		if (*name == NULL)
			return (ERROR);
	}
	return (SUCCESS);
}

/*
** Crée une nouvelle variable d'environnement
** @param name: nom de la variable
** @param value: valeur de la variable (peut être NULL)
** @return: nouvelle variable ou NULL en cas d'erreur
*/
t_env	*create_env_var(const char *name, const char *value)
{
	t_env *new_var;

	new_var = malloc(sizeof(t_env));
	if (new_var == NULL)
		return (NULL);
	new_var->id = ft_strdup(name);
	if (value != NULL)
	{
		new_var->value = ft_strdup(value);
		new_var->raw = ft_strjoin(name, "=");
	new_var->raw = ft_strjoin_free(new_var->raw, value); // ATTENTION J'AI MODIFIE FT_STR_JOIN_FREE POUR QU'il PRENNE UNE CONSTANTE EN 2EME PARAMETRE
	}
	else
	{
		new_var->value = NULL;
		new_var->raw = ft_strdup(name);
	}
	new_var->next = NULL;
	return (new_var);
}

/*
** Met à jour une variable d'environnement existante
** @param var: variable à mettre à jour
** @param name: nouveau nom
** @param value: nouvelle valeur
** @return: SUCCESS en cas de succès, ERROR sinon
*/
int update_existing_var(t_env *var, const char *name, const char *value)
{
	free(var->raw);
	if (value != NULL)
	{
		var->raw = ft_strjoin(name, "=");
		var->raw = ft_strjoin_free(var->raw, value);
		free(var->value);
		var->value = ft_strdup(value);
	}
	else
		var->raw = ft_strdup(name);
	return (SUCCESS);
}
