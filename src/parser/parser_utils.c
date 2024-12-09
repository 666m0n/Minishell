/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:48:17 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/09 21:29:02 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redirections(t_redirection *redirections)
{
	t_redirection	*tmp;

	while (redirections)
	{
		tmp = redirections;
		redirections = redirections->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->args)
			free_double(tmp->args);
		if (tmp->redirections)
			free_redirections(tmp->redirections);
		if (tmp->path)
			free(tmp->path);
		if (tmp->fd)
			free(tmp->fd);
		free(tmp);
	}
}

int	is_redir(t_token type)
{
	if (type == T_APPEND || type == T_REDIRIN || \
		type == T_REDIROUT || type == T_HEREDOC)
		return (TRUE);
	return (FALSE);
}

static t_cmd	*create_node(t_ctx *data)
{
	t_cmd	*new;

	(void)data;
	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_cmd));
    new->ctx = data; // ajout manu
	new->args = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->redirections = NULL;
	new->fd = ft_calloc(sizeof(t_fd_state), 1);
	if (new->fd)
	{
		new->fd->stdin_backup = -1;
		new->fd->stdout_backup = -1;
		new->fd->pipe_read = -1;
		new->fd->pipe_write = -1;
		new->fd->curr_in = -1;
		new->fd->curr_out = -1;
		new->fd->last_in = NULL;
		new->fd->last_out = NULL;
	}
	return (new);
}

void	extend_cmd(t_cmd **cmd, t_ctx *data)
{
	(*cmd)->next = create_node(data);
	(*cmd)->next->prev = *cmd;
	(*cmd)->next->index = (*cmd)->index + 1;
	/*(*cmd)->next->flag_error = 0;*/
	*cmd = (*cmd)->next;
	/*data->nb_command++;*/
}
