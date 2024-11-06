/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:16:13 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/06 15:00:51 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*new_redirection(t_token_type type, char *file)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
		return (free(redir), NULL);
	redir->next = NULL;
	return (redir);
}

void	free_redirection(t_redirection *redir)
{
	t_redirection	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	add_redirection(t_simple_cmd *cmd, t_redirection *new_redir)
{
	t_redirection	*last;

	if (cmd->redirections == NULL)
		cmd->redirections = new_redir;
	else
	{
		last = cmd->redirections;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}

int	is_redirection(t_token_type type)
{
	return (type == T_INPUT || type == T_OUTPUT
		|| type == T_APPEND || type == T_HEREDOC);
}

//gestion des redirs
int	handle_redirection(t_simple_cmd *cmd, t_token *token)
{
	t_redirection	*new_redir;

	if (token->next == NULL || token->next->type != T_STRING)
		return (EXIT_FAILURE);
	new_redir = new_redirection(token->type, token->next->content);
	if (!new_redir)
		return (EXIT_FAILURE);
	add_redirection(cmd, new_redir);
	return (0);
}
