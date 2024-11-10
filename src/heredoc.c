/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:06:57 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/10 21:39:47 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Compte le nombre de heredocs dans une commande
** @param cmd: commande simple à analyser
** @return: nombre de heredocs ou 0 si aucun
*/
static int	count_heredocs(t_simple_cmd *cmd)
{
	t_redirection	*redir;
	int				count;

	count = 0;
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == HEREDOC)
			count++;
		redir = redir->next;
	}
	return (count);
}

/*
** Trouve le dernier heredoc dans une commande
** @param cmd: commande simple à analyser
** @return: dernière redirection de type heredoc ou NULL si aucune
*/
static t_redirection	*get_last_heredoc(t_simple_cmd *cmd)
{
	t_redirection	*redir;
	t_redirection	*last_heredoc;

	last_heredoc = NULL;
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == HEREDOC)
			last_heredoc = redir;
		redir = redir->next;
	}
	return (last_heredoc);
}

/*
** Vérifie si une commande contient des heredocs
** @param cmd: structure de commande à vérifier
** @return: TRUE si au moins un heredoc est trouvé, FALSE sinon
*/
t_bool	have_heredoc(t_command *cmd)
{
	t_simple_cmd	*current;

	current = cmd->cmd;
	while (current)
	{
		if (count_heredocs(current) > 0)
			return (TRUE);
		current = current->pipe;
	}
	return (FALSE);
}
