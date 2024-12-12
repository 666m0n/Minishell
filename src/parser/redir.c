/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:16:13 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/12 14:15:57 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* void	handle_redir(t_cmd *cmd, t_lexer **tokens)
{
	t_lexer			*new_tok;
	t_token			type;

	if (!tokens || !(*tokens) || !(*tokens)->next)
		return ;
	type = (*tokens)->type;
	if ((*tokens)->next->type == T_SPACE && (*tokens)->next->next)
		(*tokens) = (*tokens)->next->next;
	else if ((*tokens)->next)
		(*tokens) = (*tokens)->next;
	if (!is_cmd((*tokens)->type))
		return ;
	new_tok = create_token((*tokens)->content,
			ft_strlen((*tokens)->content), type);
	if (!new_tok)
		exit_error("create_token failed");
	if (cmd->redirections)
		add_token(&(cmd->redirections), new_tok);
	else
		cmd->redirections = new_tok;
} */

static t_redirection	*create_redir(t_token type, char *file)
{
	t_redirection	*new;

	new = ft_calloc(1, sizeof(t_redirection));
	if (!new)
		exit_error("malloc failed");
	new->type = type;
	new->file = ft_strdup(file);
	new->expand = 1;
	if (!new->file)
	{
		free(new);
		exit_error("malloc failed");
	}
	new->next = NULL;
	return (new);
}

/* void	handle_redir(t_cmd *cmd, t_lexer **tokens)
{
	t_lexer		*new_tok;
	t_token		type;

	if (!tokens || !(*tokens) || !(*tokens)->next)
		return ;
	type = (*tokens)->type;
	if ((*tokens)->next->type == T_SPACE)
	{
		if (!(*tokens)->next->next)
			return ;
		(*tokens) = (*tokens)->next->next;
	}
	else
		(*tokens) = (*tokens)->next;
	if (!is_cmd((*tokens)->type))
		return ;
	new_tok = create_redir(type, (*tokens)->content);
	if (cmd->redirections)
	{
		t_redirection *tmp = cmd->redirections;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_tok;
	}
	else
		cmd->redirections = new_tok;
} */

static int	should_expand_heredoc(t_token token_type)
{
	if (token_type == T_SQUOTE)
		return (0);
	if (token_type == T_DQUOTE)
		return (0);
	return (1);
}

static void	add_redir_to_list(t_cmd *cmd, t_redirection *new_tok)
{
	t_redirection	*tmp;

	if (cmd->redirections)
	{
		tmp = cmd->redirections;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_tok;
	}
	else
		cmd->redirections = new_tok;
}

void	handle_redir(t_cmd *cmd, t_lexer **tokens)
{
	t_redirection	*new_tok;
	t_token			type;

	if (!tokens || !(*tokens) || !(*tokens)->next)
		return ;
	type = (*tokens)->type;
	if ((*tokens)->next->type == T_SPACE)
	{
		if (!(*tokens)->next->next)
			return ;
		*tokens = (*tokens)->next->next;
	}
	else
		*tokens = (*tokens)->next;
	if (!is_cmd((*tokens)->type))
		return ;
	new_tok = create_redir(type, (*tokens)->content);
	if (!new_tok)
		return ;
	if (type == T_HEREDOC)
		new_tok->expand = should_expand_heredoc((*tokens)->type);
	add_redir_to_list(cmd, new_tok);
}
