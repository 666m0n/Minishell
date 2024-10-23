/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:31:54 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/23 11:43:14 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple_cmd	*new_simple_cmd(void)
{
	t_simple_cmd	*cmd;

	cmd = malloc(sizeof(t_simple_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->pipe = NULL;
	return (cmd);
}

void	free_simple_cmd(t_simple_cmd *cmd)
{
	t_simple_cmd	*tmp;
	int				i;

	while (cmd)
	{
		tmp = cmd->pipe;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		free_redirection(cmd->redirections);
		free(cmd);
		cmd = tmp;
	}
}

void	free_command(t_command *cmd)
{
	if (cmd != NULL)
	{
		free_simple_cmd(cmd->cmd);
		free(cmd);
	}
}
