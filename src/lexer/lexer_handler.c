/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:36:13 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/11 16:40:08 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_greater(t_lexer **token, char **str, char *new)
{
	if (*(*str + 1) == '>')
	{
		free(new);
		new = ft_strdup(">>");
		if (!new)
			return ;
		create_token(T_APPEND, new, token);
		(*str) += 2;
	}
	else
	{
		free(new);
		new = ft_strdup(">");
		if (!new)
			return ;
		create_token(T_REDIROUT, new, token);
		(*str)++;
	}
	free(new);
}

void	redir_handler(t_lexer **token, char **str)
{
	char	*new;

	new = ft_strdup("");
	if (!new)
		return ;
	if (**str == '>')
		handle_greater(token, str, new);
	else if (**str == '<')
		handle_less(token, str, new);
	else
		free(new);
}

void	pipe_handler(t_lexer **tokens, char **str)
{
	char	*new;

	if (*(*str + 1) == '|')
	{
		new = ft_strdup("||");
		if (!new)
			return ;
		create_token(T_PIPE, new, tokens);
		(*str) += 2;
		free(new);
		return ;
	}
	new = ft_strdup("|");
	if (!new)
		return ;
	create_token(T_PIPE, new, tokens);
	free(new);
	(*str)++;
}

/* static char	*handle_empty_str(t_lexer **tokens, t_token type)
{
	char	*content;

	content = (char *)malloc(1);
	if (!content)
		return (NULL);
	*content = '\0';
	create_token(type, "", tokens);
	return (content);
} */

static char	*extract_quote_content(char **str, char quote)
{
	char	*start;
	char	*content;
	int		len;

	start = *str;
	len = 0;
	while ((*str)[len] && (*str)[len] != quote)
		len++;
	if (!(*str)[len])
		return (NULL);
	content = ft_substr(start, 0, len);
	*str += len + 1;
	return (content);
}

void	quotes_handler(t_lexer **tokens, char **str)
{
	char	*content;
	char	quote;
	t_token	type;

	quote = **str;
	(*str)++;
	content = extract_quote_content(str, quote);
	if (content)
	{
		if (quote == '"')
			type = T_DQUOTE;
		else
			type = T_SQUOTE;
		create_token(type, content, tokens);
		free(content);
	}
}
