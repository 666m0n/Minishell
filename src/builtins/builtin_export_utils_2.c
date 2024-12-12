/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:53:25 by emmmarti          #+#    #+#             */
/*   Updated: 2024/12/12 19:32:42 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
