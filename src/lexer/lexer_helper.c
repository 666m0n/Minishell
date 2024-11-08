/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:36:13 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/08 15:30:57 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_close_quote(char *s, char c)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != c)
		i++;
	return (i + 1);
}


int	get_token_str_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i])
				i++;
			continue ;
		}
		if (s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '\"')
				i++;
			if (s[i])
				i++;
			continue ;
		}
		if (s[i] == '|' || s[i] == '<' || s[i] == '>' ||
				(!i && (s[i] == '\'' || s[i] == '\"')) ||
			ft_isspace(s[i]))
			break ;
		i++;
	}
	return (i);
}

int	get_token_len(char *s, t_token_type type)
{
	if (type == T_PIPE || type == T_INPUT || type == T_OUTPUT)
		return (1);
	else if (type == T_APPEND || type == T_HEREDOC)
		return (2);
	else if (type == T_STRING)
		return (get_token_str_len(s));
	else if (type == T_SQUOTE)
		return (get_close_quote(s, '\''));
	else if (type == T_DQUOTE)
		return (get_close_quote(s, '\"'));
	return (0);
}

t_token_type	get_token_type(char *s)
{
	if (!s || !*s)
		return (T_EOF);
	if (s[0] == '|')
		return (T_PIPE);
	if (s[0] == '<')
	{
		if (s[1] == '<')
			return (T_HEREDOC);
		return (T_INPUT);
	}
	if (s[0] == '>')
	{
		if (s[1] == '>')
			return (T_APPEND);
		return (T_OUTPUT);
	}
	if (s[0] == '\'')
		return (T_SQUOTE);
	if (s[0] == '\"')
		return (T_DQUOTE);
	return (T_STRING);
}

t_token	*tokenize(char *s)
{
	int				len;
	t_token			*node;
	t_token_type	type;

	len = 0;
	node = NULL;
	type = get_token_type(s);
	len = get_token_len(s, type);
	node = create_token(s, len, type);
	return (node);
}
