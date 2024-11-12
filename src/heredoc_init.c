/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:15:46 by emmmarti          #+#    #+#             */
/*   Updated: 2024/11/11 13:41:08 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Initialise une nouvelle structure heredoc
** @param delimiter: mot de fin du heredoc
** @return: structure initialisée ou NULL si erreur
*/
static t_heredoc	*init_heredoc(const char *delimiter)
{
	t_heredoc	*heredoc;

	heredoc = malloc(sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	heredoc->delimiter = ft_strdup(delimiter);
	if (!heredoc->delimiter)
	{
		free(heredoc);
		return (NULL);
	}
	heredoc->content = NULL;
	heredoc->pipe_fd[0] = -1;
	heredoc->pipe_fd[1] = -1;
	heredoc->expand_vars = TRUE;
	return (heredoc);
}

/*
** Crée un heredoc depuis une redirection
** @param redir: redirection à convertir en heredoc
** @return: heredoc créé ou NULL si erreur/pas heredoc
*/
static t_heredoc	*create_heredoc(t_redirection *redir)
{
	if (!redir || redir->type != HEREDOC || !redir->file)
		return (NULL);
	return (init_heredoc(redir->file));
}

/*
** Configure le heredoc pour une commande simple
** @param cmd: commande à configurer
** @param redir: redirection de type heredoc
** @return: SUCCESS ou ERROR
*/
static int	setup_heredoc(t_simple_cmd *cmd, t_redirection *redir)
{
	t_heredoc	*heredoc;

	if (!cmd || !redir)
		return (ERROR);
	if (cmd->heredoc)
		return (ERROR);
	heredoc = create_heredoc(redir);
	if (!heredoc)
		return (ERROR);
	cmd->heredoc = heredoc;
	return (SUCCESS);
}

/*
** Identifie et configure les heredocs d'une commande simple
** @param cmd: commande à analyser
** @return: SUCCESS ou ERROR
*/
int	identify_heredoc(t_simple_cmd *cmd)
{
	t_redirection	*current;

	if (!cmd)
		return (ERROR);
	current = cmd->redirections;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (setup_heredoc(cmd, current) == ERROR)
				return (ERROR);
		}
		current = current->next;
	}
	return (SUCCESS);
}

/*
** Identifie tous les heredocs d'une commande avec pipes
** @param cmd: commande à analyser
** @return: SUCCESS ou ERROR
*/
int	identify_all_heredocs(t_command *cmd)
{
	t_simple_cmd	*current;

	if (!cmd || !cmd->cmd)
		return (ERROR);
	current = cmd->cmd;
	while (current)
	{
		if (identify_heredoc(current) == ERROR)
			return (ERROR);
		current = current->pipe;
	}
	return (SUCCESS);
}
