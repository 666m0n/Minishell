/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:47:22 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/12 13:09:49 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_exit_status(t_cmd *cmd, int status)
{
	if (cmd)
		cmd->exit_status = status;
}

int	set_cmd_path(t_cmd *cmd, char *path)
{
	if (!cmd)
		return (ERROR);
	cmd->path = path;
	return (SUCCESS);
}

int	set_fd_backup(t_cmd *cmd, int fd_in, int fd_out)
{
	if (!cmd || !cmd)
		return (ERROR);
	cmd->stdin_backup = fd_in;
	cmd->stdout_backup = fd_out;
	return (SUCCESS);
}
