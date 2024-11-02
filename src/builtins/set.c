/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:47:22 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/01 11:46:11 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_exit_status(t_command *cmd, int status)
{
	if (cmd)
		cmd->exit_status = status;
}

int set_command_path(t_command *cmd, char *path)
{
    if (!cmd || !cmd->cmd)
        return (ERROR);
    cmd->cmd->path = path;
    return (SUCCESS);
}
