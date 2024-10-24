/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42Paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:36:13 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/22 22:46:40 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*result;
	size_t	len;
	size_t	i;

	len = 0;
	while (len < n && s[len] != '\0')
	{
		len++;
	}
	result = (char *)malloc(len + 1);
	if (!result)
	{
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[len] = '\0';
	return (result);
}

int	quote_len(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

// calcule la longueur de chaque mot, et obtient directement la longueur
//des trucs quoted
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
	else if (type == INFILE || type == OUTFILE || type == PIPE
		|| type == ESPACE)
		len = 1;
	else
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
	else if (str[0] == ' ')
		return (ESPACE);
	else if (str[0] == '\"')
		return (D_QUOTE);
	else if (str[0] == '\'')
		return (S_QUOTE);
	return (STRING);
}
