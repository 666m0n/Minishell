/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:58:12 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/26 14:04:28 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_redir_target(t_token type)
{
	return (type == T_CMD || type == T_STRING || type == T_SQUOTE
		|| type == T_DQUOTE);
}

static int	check_redirection(t_syntax *tokens)
{
	if (!tokens->next)
		return (handle_syntax_error("newline"));
	if (!valid_redir_target(tokens->next->type))
	{
		if (tokens->next->type == T_PIPE)
			return (handle_syntax_error(tokens->next->content));
		return (handle_syntax_error(tokens->next->content));
	}
	return (SUCCESS);
}

static int	check_pipe(t_syntax *tokens)
{
	if (!tokens->prev || !tokens->next)
		return (handle_syntax_error("|"));
	if (tokens->next->type == T_PIPE)
		return (handle_syntax_error("||"));
	return (SUCCESS);
}

static int	check_syntax_rules(t_syntax *curr)
{
	if (is_redir(curr->type))
		return (check_redirection(curr));
	if (curr->type == T_PIPE)
		return (check_pipe(curr));
	return (SUCCESS);
}

t_return	syntax_tokens(t_lexer *tokens)
{
	t_syntax	*curr;
	t_syntax	*syntax_list;
	int			status;

	if (!tokens)
		return (ERROR);
	syntax_list = create_syntax_list(tokens);
	if (!syntax_list)
		return (ERROR);
	curr = syntax_list;
	while (curr)
	{
		status = check_syntax_rules(curr);
		if (status != SUCCESS)
		{
			free_syntax_list(syntax_list);
			return (status);
		}
		curr = curr->next;
	}
	free_syntax_list(syntax_list);
	return (SUCCESS);
}
