/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:38:06 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/09 19:03:15 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:45:17 by your_login        #+#    #+#             */
/*   Updated: 2024/11/09 15:45:17 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Vérifie si la commande contient des heredocs
** @param cmd: commande à vérifier
** @return: TRUE si heredoc présent, FALSE sinon
*/
t_bool	has_heredoc(t_command *cmd)
{
	t_redirection	*redir;

	if (!cmd || !cmd->cmd)
		return (FALSE);
	redir = cmd->cmd->redirections;
	while (redir)
	{
		if (redir->type == HEREDOC)
			return (TRUE);
		redir = redir->next;
	}
	return (FALSE);
}

/*
** Vérifie si la commande contient des redirections
** @param cmd: commande à vérifier
** @return: TRUE si redirections présentes, FALSE sinon
*/
t_bool	has_redirections(t_command *cmd)
{
	if (!cmd || !cmd->cmd)
		return (FALSE);
	return (cmd->cmd->redirections != NULL);
}

/*
** Traite les heredocs de la commande
** @param cmd: commande à traiter
** @return: SUCCESS si ok, ERROR si erreur
*/
int	process_heredocs(t_command *cmd)
{
	t_redirection	*redir;
	t_heredoc		*current;

	redir = cmd->cmd->redirections;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			current = create_heredoc(redir->file);
			if (!current)
				return (ERROR);
			if (setup_single_heredoc(current) != SUCCESS)
				return (ERROR);
			if (read_heredoc_content(current) != SUCCESS)
				return (ERROR);
			add_heredoc_to_list(cmd->ctx, current);
		}
		redir = redir->next;
	}
	return (SUCCESS);
}

/*
** Configure les redirections pour la commande
** @param cmd: commande à configurer
** @return: SUCCESS si ok, ERROR si erreur
*/
int	setup_redirections(t_command *cmd)
{
	t_redirection	*redir;
	int				status;

	redir = cmd->cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			status = handle_input_redirection(cmd->cmd, redir);
		else if (redir->type == REDIR_OUT || redir->type == APPEND)
			status = handle_output_redirection(cmd->cmd, redir);
		else if (redir->type == HEREDOC)
			status = handle_heredoc_redirection(cmd->cmd, redir);
		if (status != SUCCESS)
			return (status);
		redir = redir->next;
	}
	return (SUCCESS);
}

/*
** Prépare la commande pour l'exécution
** @param cmd: commande à préparer
** @return: SUCCESS si ok, ERROR si erreur
*/
int	prepare_command(t_command *cmd)
{
	if (init_command_fds(cmd->cmd) != SUCCESS)
		return (ERROR);
	if (has_heredoc(cmd) && process_heredocs(cmd) != SUCCESS)
		return (ERROR);
	if (has_redirections(cmd) && setup_redirections(cmd) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
