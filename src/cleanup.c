/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:26:40 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/15 11:28:37 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Ferme tous les descripteurs de fichiers ouverts d'une commande
** @param cmd: structure de commande
** Note: gère les backups stdin/stdout et les pipes de heredoc
*/
void cleanup_fds(t_cmd *cmd)
{
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
