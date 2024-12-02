/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:58:12 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/02 09:07:08 by sviallon         ###   ########.fr       */
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
	if (!curr || !curr->content)
		return (SUCCESS);
	if (is_redir(curr->type))
		return (check_redirection(curr));
	if (curr->type == T_PIPE)
		return (check_pipe(curr));
	if (is_directory(curr->content) && (curr->next == NULL
			&& curr->prev == NULL))
		return (handle_misc(curr));
	if (curr->content[0] == '#' || curr->content[0] == '!'
		|| curr->content[0] == ':')
		return (handle_misc(curr));
	return (SUCCESS);
}

t_return	syntax_tokens(t_lexer *tokens, t_ctx *data)
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
			change_exit_code(status, data);
			free_syntax_list(syntax_list);
			return (status);
		}
		curr = curr->next;
	}
	free_syntax_list(syntax_list);
	return (SUCCESS);
}
