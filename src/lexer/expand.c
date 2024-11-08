/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:53:16 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/08 14:10:02 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_var_len(const char *str)
{
	size_t	i;

	if (!str || !*str)
		return (0);
	if (*str == '?')
		return (1);
	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

static char	*get_var_value(const char *var_name, t_env *env, int last_exit)
{
	t_env	*current;

	if (!var_name || !*var_name)
		return (ft_strdup("$"));
	if (*var_name == '?')
		return (ft_itoa(last_exit));
	if (ft_isdigit(*var_name))
		return (ft_strdup(""));
	current = env;
	while (current)
	{
		if (!ft_strcmp(current->id, var_name))
			return (current->value ? ft_strdup(current->value) : ft_strdup(""));
		current = current->next;
	}
	return (ft_strdup(""));
}

static char	*join_parts(char *result, char *value)
{
	char	*tmp;

	if (!result)
		return (value);
	tmp = ft_strjoin(result, value);
	free(result);
	free(value);
	return (tmp);
}

char	*expand_token_content(char *content, t_env *env, int last_exit)
{
	char	*result;
	char	*var_name;
	char	*value;
	size_t	i;
	size_t	var_len;

	result = NULL;
	i = 0;
	while (content[i])
	{
		if (content[i] == '$' && content[i + 1])
		{
			if (i > 0)
				result = join_parts(result, ft_strndup(content, i));
			var_len = get_var_len(content + i + 1);
			var_name = ft_strndup(content + i + 1, var_len);
			value = get_var_value(var_name, env, last_exit);
			free(var_name);
			result = join_parts(result, value);
			content += i + var_len + 1;
			i = 0;
		}
		else
			i++;
	}
	if (!result || content[0])
		result = join_parts(result, ft_strdup(content));
	return (result);
}

int	expand_variables(t_token *tokens, t_env *env, int last_exit)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->expandable && current->content &&
			ft_strchr(current->content, '$'))
		{
			expanded = expand_token_content(current->content, env, last_exit);
			if (!expanded)
				return (0);
			free(current->content);
			current->content = expanded;
		}
		current = current->next;
	}
	return (1);
}
