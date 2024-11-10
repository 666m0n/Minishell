/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:35:12 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/10 21:41:33 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Crée un heredoc actif (dernier de la séquence)
** @param redir: redirection heredoc à traiter
** @return: structure heredoc ou NULL si erreur
*/
static t_heredoc	*create_active_heredoc(t_redirection *redir)
{
	t_heredoc	*new;

	new = malloc(sizeof(t_heredoc));
	if (!new)
		return (NULL);
	new->delimiter = ft_strdup(redir->file);
	if (!new->delimiter)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->content = NULL;
	new->pipe_fd[0] = -1;
	new->pipe_fd[1] = -1;
	return (new);
}

/*
** Crée un heredoc inactif (sera lu mais ignoré)
** @param redir: redirection heredoc à traiter
** @return: structure heredoc ou NULL si erreur
*/
static t_heredoc	*create_inactive_heredoc(t_redirection *redir)
{
	t_heredoc	*new;

	new = malloc(sizeof(t_heredoc));
	if (!new)
		return (NULL);
	new->delimiter = ft_strdup(redir->file);
	if (!new->delimiter)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->content = NULL;
	new->pipe_fd[0] = -1;
	new->pipe_fd[1] = -1;
	return (new);
}

/*
** Ajoute un heredoc à la liste des heredocs en attente
** @param ctx: contexte du shell
** @param new: nouveau heredoc à ajouter
*/
static void	add_heredoc_to_list(t_ctx *ctx, t_heredoc *new)
{
	t_heredoc	*current;

	if (!ctx->pend_heredocs)
	{
		ctx->pend_heredocs = new;
		return ;
	}
	current = ctx->pend_heredocs;
	while (current->next)
		current = current->next;
	current->next = new;
}

/*
** Collecte tous les heredocs d'une commande simple
** @param cmd: commande simple à analyser
** @param ctx: contexte du shell
** @return: SUCCESS ou ERROR
*/
int	collect_heredocs(t_command *cmd, t_ctx *ctx)
{
	t_redirection	*redir;
	t_redirection	*last;
	t_heredoc		*new;

	last = get_last_heredoc(cmd->cmd);
	redir = cmd->cmd->redirections;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			if (redir == last)
				new = create_active_heredoc(redir);
			else
				new = create_inactive_heredoc(redir);
			if (!new)
				return (ERROR);
			add_heredoc_to_list(ctx, new);
		}
		redir = redir->next;
	}
	return (SUCCESS);
}
