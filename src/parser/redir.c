/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:16:13 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/23 11:46:21 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*new_redirection(t_token type, char *file)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
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
	t_redirection	*current;

	if (cmd->redirections == NULL)
	{
		cmd->redirections = new_redir;
		return ;
	}
	current = cmd->redirections;
	while (current->next != NULL)
		current = current->next;
	current->next = new_redir;
}
