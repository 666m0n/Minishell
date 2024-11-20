/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:36:13 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/20 15:14:52 by sviallon         ###   ########.fr       */
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

/* void	quotes_handler(t_lexer **tokens, char **str)
{
	char	quote;
	char	*start;
	char	*content;

	quote = **str;
	start = ++(*str);
	while (**str && **str != quote)
		(*str)++;
	content = ft_substr(start, 0, *str - start);
	if (content[0] == '\0')
	{
		return (free(content));
	}
	if (**str == quote)
	{
		if (quote == '\'')
			create_token(T_SQUOTE, content, tokens);
		else
			create_token(T_DQUOTE, content, tokens);
		(*str)++;
	}
	else
		create_token(T_UNKNOWN, ft_strjoin(ft_strdup(start - 1), content),
			tokens);
	free(content);
} */

static int	get_quote_content(char **str, char **content, char quote)
{
    char    *start;
    int     len;
    char    curr_quote;
    int     quote_count;

    start = ++(*str);
    len = 0;
    quote_count = 1;  // On a déjà vu une quote
    while (**str)
    {
        curr_quote = **str;
        if (curr_quote == quote)
        {
            quote_count++;
            if (quote_count % 2 == 0)  // Quote fermante trouvée
                break;
        }
        (*str)++;
        len++;
    }
    *content = ft_substr(start, 0, len);
    if (!*content)
        return (0);
    if (**str == quote)
        (*str)++;
    return (1);
}

void	quotes_handler(t_lexer **tokens, char **str)
{
	char	*content;
	char	quote;

	quote = **str;
	if (!get_quote_content(str, &content, quote))
		return ;
	if (quote == '\'')
		create_token(T_SQUOTE, content, tokens);
	else
		create_token(T_DQUOTE, content, tokens);
	free(content);
}
