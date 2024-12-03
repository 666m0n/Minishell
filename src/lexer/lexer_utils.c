/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:35:30 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/03 17:02:41 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_less(t_lexer **token, char **str, char *new)
{
	if (*(*str + 1) == '<')
	{
		free(new);
		new = ft_strdup("<<");
		if (!new)
			return ;
		create_token(T_HEREDOC, new, token);
		(*str) += 2;
	}
	else
	{
		free(new);
		new = ft_strdup("<");
		if (!new)
			return ;
		create_token(T_REDIRIN, new, token);
		(*str)++;
	}
	free(new);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

void	init_token(t_lexer *new_token, t_token type, char *content)
{
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->content = ft_strdup(content);
	if (!new_token->content)
		return ;
	new_token->type = type;
	new_token->index = 0;
}

t_lexer	*lst_getlast(t_lexer *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

void	create_token(t_token type, char *content, t_lexer **tokens)
{
	t_lexer	*new_token;
	t_lexer	*last;

	if (!content || !tokens)
		return ;
	new_token = ft_calloc(1, sizeof(t_lexer));
	if (!new_token)
		return ;
	init_token(new_token, type, content);
	if (!*tokens)
	{
		*tokens = new_token;
		new_token->prev = NULL;
		new_token->next = NULL;
	}
	else
	{
		last = lst_getlast(*tokens);
		last->next = new_token;
		new_token->prev = last;
	}
}
