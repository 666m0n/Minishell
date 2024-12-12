/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:46:42 by emmmarti          #+#    #+#             */
/*   Updated: 2024/12/12 18:49:20 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Initialise les descripteurs de fichiers pour une commande
** @param fd: structure de fichiers de la commande
*/
void	initialize_fd(t_fd_state *fd)
{
	fd->curr_in = -1;
	fd->curr_out = -1;
	fd->last_in = NULL;
	fd->last_out = NULL;
}

/*
** Gère les redirections d'entrée
** @param cmd_fd: structure de fichiers de la commande
** @param redir: redirection en cours
*/
void	handle_input_redirection(t_fd_state *cmd_fd, t_redirection *redir)
{
	cmd_fd->curr_in = 1;
	cmd_fd->last_in = redir;
}

/*
** Gère les redirections de sortie
** @param cmd_fd: structure de fichiers de la commande
** @param redir: redirection en cours
*/
void	handle_output_redirection(t_fd_state *cmd_fd, t_redirection *redir)
{
	int	flags;
	int	fd;

	if (redir->type == T_REDIROUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(redir->file, flags, 0644);
	if (fd != -1)
		close(fd);

	cmd_fd->curr_out = 1;
	cmd_fd->last_out = redir;
}
