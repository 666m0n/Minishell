/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:26:40 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/14 10:31:25 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Ferme les backups s'ils sont ouverts
** Ferme les pipes de heredoc s'ils sont ouverts
** Reset des FDs à -1 pour éviter une double fermeture
*/
void cleanup_fds(t_cmd *cmd)
{
	if (!cmd || !cmd->fd)
		return ;

	if (cmd->fd->stdin_backup > 2)
		close(cmd->fd->stdin_backup);
	if (cmd->fd->stdout_backup > 2);
		close(cmd->fd->stdout_backup);
    if (cmd->fd->pipe_read > 2)
        close(cmd->fd->pipe_read);
    if (cmd->fd->pipe_write > 2)
        close(cmd->fd->pipe_write);
    cmd->fd->stdin_backup = -1;
    cmd->fd->stdout_backup = -1;
    cmd->fd->pipe_read = -1;
    cmd->fd->pipe_write = -1;
}

/*
** Ferme les descripteurs en cas d'erreur
*/
void	cleanup_fds(t_cmd *cmd)
{
	close(cmd->fd->stdin_backup);
	close(cmd->fd->stdout_backup);
}

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
