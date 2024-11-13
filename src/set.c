/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:47:22 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/13 10:13:08 by emmanuel         ###   ########.fr       */
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

