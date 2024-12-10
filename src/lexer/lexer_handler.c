/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:36:13 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/10 16:10:39 by sviallon         ###   ########.fr       */
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

static char	*handle_empty_str(t_lexer **tokens, t_token type)
{
	char	*content;

	content = (char *)malloc(1);
	if (!content)
		return (NULL);
	*content = '\0';
	create_token(type, "", tokens);
	return (content);
}

void	quotes_handler(t_lexer **tokens, char **str)
{
	char	quote;
	char	changed;
	char	*content;
	int		effective_q;

	quote = **str;
	changed = quote;
	skip_consecutive_quotes(str, &quote, &effective_q);
	if (**str == '\0')
	{
		content = handle_empty_str(tokens, get_quote_type(quote));
		if (content)
			free(content);
		return ;
	}
	if (**str == '\'' || **str == '"')
		(*str)++;
	content = get_quote_content(str, quote, changed);
	if (!content || content[0] == '\0')
		return (free(content));
	create_token(get_quote_type(quote), content, tokens);
	if (**str)
		(*str)++;
	free(content);
}
