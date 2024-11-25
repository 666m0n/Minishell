/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:33:05 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/25 15:57:59 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_str(char *str, char c)
{
	int		len;
	char	*new_str;

	if (!str)
		str = ft_strdup("");
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new_str = ft_realloc(str, len, len + 2);
	if (!new_str)
		return (free(str), NULL);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

static char	*expand_var(char *s, t_ctx *data, size_t *i, char *result)
{
	char	*tmp;
	char	*new_res;
	int		len;

	tmp = replace_var(s, data, i);
	if (!tmp)
		return (free(result), NULL);
	len = ft_strlen(result) + ft_strlen(tmp);
	new_res = ft_calloc(len + 2, sizeof(char));
	if (!new_res)
	{
		if (result)
			free(result);
		if (tmp)
			free(tmp);
		return (NULL);
	}
	ft_strcpy(new_res, result);
	ft_strcat(new_res, tmp);
	if (result)
		free(result);
	if (tmp)
		free(tmp);
	return (new_res);
}

static char	*print_dollar(char *s, size_t *i, char *result)
{
	char	*tmp;
	char	*new_result;
	char	*pid_str;
	pid_t	current_pid;

	tmp = NULL;
	if (s[*i + 1] == '$')
	{
		current_pid = fork();
		if (current_pid == 0)
			exit(0);
		else if (current_pid > 0)
		{
			wait(NULL);
			pid_str = ft_itoa(current_pid - 1);
			tmp = pid_str;
		}
		(*i)++;
	}
	else
		tmp = ft_strdup("$");
	new_result = ft_strjoin(result, tmp);
	free(tmp);
	free(result);
	return (new_result);
}

static char	*replace_dollar(char *s, t_ctx *data)
{
	size_t		i;
	char		*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$' && (s[i + 1] == '\0' || s[i + 1] == '$'
				|| ft_isspace(s[i + 1])))
			result = print_dollar(s, &i, result);
		else if (s[i] == '$' && (s[i + 1] >= '1' && s[i + 1] <= '9'))
			i++;
		else if (s[i] == '$' && (s[i + 1] < '1' || s[i + 1] > '9'))
		{
			result = expand_var(s, data, &i, result);
			i += get_var_len(s, &i);
		}
		else
			result = copy_str(result, s[i]);
		i++;
	}
	return (result);
}

void	handle_dollar(t_lexer *token, t_ctx *data)
{
	char	*new_token;

	while (token)
	{
		if ((token->type == T_STRING || token->type == T_DQUOTE || \
			(token->type == T_CMD && token->content[0] == '$')) \
			&& !(token->prev && token->prev->type == T_HEREDOC) \
			&& !(token->prev && token->prev->type == T_SPACE \
			&& token->prev->prev && \
							token->prev->prev->type == T_HEREDOC))
		{
			new_token = replace_dollar(token->content, data);
			if (new_token)
			{
				free(token->content);
				token->content = new_token;
			}
		}
		token = token->next;
	}
}
