/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:10:35 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/07 12:24:09 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//trouve la valeur de $var
char	*get_env_value(t_env *env, const char *var_name)
{
	while (env)
	{
		if (ft_strncmp(env->id, var_name, ft_strlen(var_name) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

size_t	calculate_expanded_length(const char *str, t_env *env, int exit_status)
{
	size_t	len;
	size_t	i;
	char	*var_value;
	char	var_name[256];
	int		j;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
			{
				len += ft_intlen(exit_status);
				i++;
				continue ;
			}
			j = 0;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && j < 255)
				var_name[j++] = str[i++];
			var_name[j] = '\0';
			if (j > 0)
			{
				var_value = get_env_value(env, var_name);
				if (var_value)
					len += ft_strlen(var_value);
			}
			else
				len++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

//fonction qui expand et stock dans une chaine
char	*expand_variables(const char *str, t_env *env, int exit_status)
{
	size_t	new_len;
	char	*result;
	size_t	i;
	size_t	j;
	char	var_name[256];
	char	*var_value;
	char	*exit_str;
	int		k;

	new_len = calculate_expanded_length(str, env, exit_status);
	result = malloc(new_len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && j < new_len)
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
			{
				exit_str = ft_itoa(exit_status);
				if (exit_str)
				{
					ft_strlcpy(&result[j], exit_str, new_len - j + 1);
					j += ft_strlen(exit_str);
					free(exit_str);
					i++;
				}
				continue ;
			}
			k = 0;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && k < 255)
				var_name[k++] = str[i++];
			var_name[k] = '\0';
			if (k > 0)
			{
				var_value = get_env_value(env, var_name);
				if (var_value)
				{
					ft_strlcpy(&result[j], var_value, new_len - j + 1);
					j += ft_strlen(var_value);
				}
			}
			else if (str[i - 1] == '$')
				result[j++] = '$';
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	expand_token_variables(t_token *token, t_ctx *ctx)
{
	char	*expanded;

	if (!token->expandable || !ft_strchr(token->content, '$'))
		return (SUCCESS);
	expanded = expand_variables(token->content, ctx->envp, ctx->exit_code);
	if (!expanded)
		return (EXIT_FAILURE);
	free(token->content);
	token->content = expanded;
	return (SUCCESS);
}

//parcourt tous les tokens et expand les bonnes variables
int	expand_all_variables(t_token *tokens, t_ctx *ctx)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (expand_token_variables(current, ctx) != 0)
			return (1);
		current = current->next;
	}
	return (0);
}
