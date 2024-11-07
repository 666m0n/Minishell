/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:53:16 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/07 17:49:19 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_expanded_var_size(const char *str, t_lexer *lexer)
{
	char	*var_name;
	char	*var_value;
	size_t	var_len;
	size_t	value_len;

	var_len = get_var_name_len(str);
	if (!var_len)
		return (0);
	var_name = ft_strndup(str, var_len);
	if (!var_name)
		return (0);
	var_value = get_var_value(var_name, lexer);
	free(var_name);
	if (!var_value)
		return (0);
	value_len = ft_strlen(var_value);
	free(var_value);
	return (value_len);
}

size_t	calculate_expanded_size(char *str, t_lexer *lexer)
{
	size_t	size;
	size_t	i;
	size_t	var_size;

	size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			var_size = get_expanded_var_size(str + i + 1, lexer);
			size += var_size;
			i += get_var_name_len(str + i + 1) + 1;
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

//expand une seule variable dans la chaine
size_t	expand_single_var(char *result, char *str, size_t j, t_lexer *lexer)
{
	char	*var_name;
	char	*var_value;
	size_t	var_len;

	var_len = get_var_name_len(str);
	var_name = ft_strndup(str, var_len);
	if (!var_name)
		return (j);
	var_value = get_var_value(var_name, lexer);
	free(var_name);
	if (!var_value)
		return (j);
	j = copy_var_value(result, j, var_value, ft_strlen(result));
	free(var_value);
	return (j);
}

//expand toutes les var dans une chaine
char	*expand_string(char *str, t_lexer *lexer)
{
	char	*result;
	size_t	size;
	size_t	i;
	size_t	j;

	size = calculate_expanded_size(str, lexer);
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && j < size)
	{
		if (str[i] == '$' && str[i + 1])
		{
			j = expand_single_var(result, str + i + 1, j, lexer);
			i += get_var_name_len(str + i + 1) + 1;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	expand_variables(t_token *tokens, t_lexer *lexer)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->expandable && ft_strchr(current->content, '$'))
		{
			expanded = expand_string(current->content, lexer);
			if (!expanded)
				return (0);
			free(current->content);
			current->content = expanded;
		}
		current = current->next;
	}
	return (1);
}
