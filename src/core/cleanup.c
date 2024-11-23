/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:26:40 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/22 10:20:19 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Ferme tous les descripteurs de fichiers ouverts d'une commande
** et nettoie les fichiers temporaires des heredocs
** @param cmd: structure de commande
*/
void	cleanup_fds(t_cmd *cmd)
{
	t_redirection	*redir;

	if (!cmd || !cmd->fd)
		return ;
	if (cmd->fd->stdin_backup > 2)
		close(cmd->fd->stdin_backup);
	if (cmd->fd->stdout_backup > 2)
		close(cmd->fd->stdout_backup);
	if (cmd->fd->pipe_read > 2)
		close(cmd->fd->pipe_read);
	if (cmd->fd->pipe_write > 2)
		close(cmd->fd->pipe_write);
	cmd->fd->stdin_backup = -1;
	cmd->fd->stdout_backup = -1;
	cmd->fd->pipe_read = -1;
	cmd->fd->pipe_write = -1;
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == T_HEREDOC && redir->file
			&& ft_strncmp(redir->file, "/tmp/heredoc_", 13) == 0)
		{
			unlink(redir->file);
			free(redir->file);
			redir->file = NULL;
		}
		redir = redir->next;
	}
}

/*
** Ferme tous les descripteurs de fichiers des pipes restants
** @param pipe_array: tableau de pipes à nettoyer
** @param nb_of_pipes: nombre de pipes dans le tableau
** Note: utilisé après l'exécution du pipeline pour éviter les fuites
*/
void	cleanup_remaining_pipes(t_pipe *pipe_array, int nb_of_pipes)
{
	int	i;

	i = 0;
	while (i < nb_of_pipes)
	{
		close(pipe_array[i][0]);
		close(pipe_array[i][1]);
		i++;
	}
}

/*
** Libère un tableau de chaînes de caractères et le tableau lui-même
** @param array: tableau à libérer
** Note: gère le cas où array est NULL
*/
void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
