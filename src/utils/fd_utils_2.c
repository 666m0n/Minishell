/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:34:21 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/09 17:35:13 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Configure une redirection pour un fichier
** @param type: type de redirection (REDIR_IN, REDIR_OUT, APPEND)
** @param file: nom du fichier
** @param fd_set: structure de FDs à configurer
** @return: SUCCESS si ok, ERROR si erreur
*/
static int	setup_redirection(t_token type, char *file, t_fd_set *fd_set)
{
	int	flags;
	int	fd;

	if (!file || !fd_set)
		return (ERROR);
	if (type == REDIR_IN)
		flags = O_RDONLY;
	else if (type == REDIR_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (type == APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		return (ERROR);
	fd = open(file, flags, 0644);
	if (fd == SYSCALL_ERROR)
		return (handle_system_error(file));
	fd_set->current = fd;
	return (SUCCESS);
}

/*
** Applique une redirection d'entrée
** @param cmd: commande simple contenant la redirection
** @param redir: redirection à appliquer
** @return: SUCCESS si ok, ERROR si erreur
*/
static int	handle_input_redirection(t_simple_cmd *cmd, t_redirection *redir)
{
	return (setup_redirection(redir->type, redir->file, &cmd->input));
}

/*
** Applique une redirection de sortie
** @param cmd: commande simple contenant la redirection
** @param redir: redirection à appliquer
** @return: SUCCESS si ok, ERROR si erreur
*/
static int	handle_output_redirection(t_simple_cmd *cmd, t_redirection *redir)
{
	return (setup_redirection(redir->type, redir->file, &cmd->output));
}

/*
** Applique toutes les redirections d'une commande
** @param cmd: commande simple contenant les redirections
** @return: SUCCESS si ok, ERROR si erreur
*/
int	apply_redirections(t_simple_cmd *cmd)
{
	t_redirection	*redir;
	int				status;

	if (!cmd)
		return (ERROR);
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			status = handle_input_redirection(cmd, redir);
		else if (redir->type == REDIR_OUT || redir->type == APPEND)
			status = handle_output_redirection(cmd, redir);
		else
			return (ERROR);
		if (status != SUCCESS)
			return (status);
		redir = redir->next;
	}
	return (SUCCESS);
}
