/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:36:13 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/22 22:21:31 by sviallon         ###   ########.fr       */
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

void	space_handler(t_lexer **tokens, char **str)
{
	char	*new;

	new = malloc(sizeof(char) * 2);
	if (!new)
		return ;
	new[0] = **str;
	new[1] = '\0';
	if (ft_isspace(**str))
	{
		create_token(T_SPACE, new, tokens);
		while (**str && ft_isspace(**str))
			(*str)++;
	}
	free(new);
}

void	quotes_handler(t_lexer **tokens, char **str)
{
	char	quote;
	char	*content;
	int		effective_q;

	if (!str || !*str)
		return ;
	quote = **str;
	while (**str && (**str == '\'' || **str == '"'))
	{
		skip_consecutive_quotes(str, &quote, &effective_q);
		(*str)++;
	}
	if (!effective_q && **str && (**str == '\'' || **str == '"'))
		quote = **str;
	content = get_quote_content(str, quote);
	if (content[0] == '\0')
		return (free(content));
	/* if (!effective_q && (**str == '$' || **str)) */
	create_token(get_quote_type(quote), content, tokens);
	(*str)++;
	free(content);
}
