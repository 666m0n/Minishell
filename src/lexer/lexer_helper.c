/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:36:13 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/14 14:05:51 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_len(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

int	get_str_len(char *str)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '\'')
			i += quote_len(&(str[i]), '\'');
		else if (str[i] == '\"')
			i += quote_len(&(str[i]), '\"');
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>'
			|| str[i] == ' ' || str[i] == '\t' || str[i] == '\''
			|| str[i] == '\"')
			break ;
		i++;
	}
	return (i);
}

int	lex_get_len(char *str, t_token type)
{
	int	len;

	len = 0;
	if (type == HEREDOC || type == APPEND)
		len = 2;
	else if (type == INFILE || type == OUTFILE || type == PIPE)
		len = 1;
	else if (type == STRING)
		len = get_str_len(str);
	return (len);
}

t_token	lex_get_type(char *str)
{
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (HEREDOC);
		else
			return (INFILE);
	}
	else if (str[0] == '>')
	{
		if (str[1] == '>')
			return (APPEND);
		else
			return (OUTFILE);
	}
	else if (str[0] == '|')
		return (PIPE);
	return (STRING);
}
