/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:05:03 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/18 18:03:20 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_existing_var(t_env *env, const char *name)
{
	t_env	*current;
	int		len;

	len = 0;
	while (name[len] && name[len] != '=')
		len++;
	current = env;
	while (current)
	{
		if (!ft_strncmp(current->id, name, len) && !current->id[len])
			return (current);
		current = current->next;
	}
	return (NULL);
}

char	*extract_value(const char *arg)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (NULL);
	return (ft_strdup(eq + 1));
}

t_env	*create_var(const char *arg, char *value)
{
	t_env	*new;
	int		len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->id = ft_strndup(arg, len);
	new->value = value;
	new->raw = ft_strdup(arg);
	new->next = NULL;
	if (!new->id || !new->raw)
	{
		free_env_var(new);
		return (NULL);
	}
	return (new);
}

t_env	*update_env_variable(t_ctx *ctx, char *arg)
{
	t_env	*var;
	char	*new_value;

	var = find_existing_var(ctx->envp, arg);
	new_value = extract_value(arg);
	if (var)
	{
		free(var->value);
		free(var->raw);
		var->value = new_value;
		var->raw = ft_strdup(arg);
		if (!var->raw)
			return (NULL);
		return (var);
	}
	var = create_var(arg, new_value);
	if (!var)
		return (NULL);
	var->next = ctx->envp;
	ctx->envp = var;
	return (var);
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
