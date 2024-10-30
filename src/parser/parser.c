/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:43:15 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/30 10:59:44 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_argument(t_simple_cmd *cmd, t_pars_node *token)
{
	char	**new_args;
	int		i;

	i = 0;
	if (cmd->args != NULL)
	{
		while (cmd->args[i] != NULL)
			i++;
	}
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (EXIT_FAILURE);
	i = 0;
	if (cmd->args != NULL)
	{
		while (cmd->args[i] != NULL)
		{
			new_args[i] = cmd->args[i];
			i++;
		}
	}
	new_args[i] = ft_strdup(token->content);
	if (new_args[i] == NULL)
	{
		free(new_args);
		return (EXIT_FAILURE);
	}
	new_args[i + 1] = NULL;
	if (cmd->args != NULL)
		free(cmd->args);
	cmd->args = new_args;
	return (0);
}

t_command	*parser(t_pars_node *tokens)
{
	t_command		*cmd;
	t_simple_cmd	*current_cmd;

	cmd = malloc(sizeof(t_command));
	if (cmd == NULL)
		return (NULL);
	cmd->exit_status = 0;
	cmd->cmd = new_simple_cmd();
	if (cmd->cmd == NULL)
	{
		free(cmd);
		return (NULL);
	}
	current_cmd = cmd->cmd;
	while (tokens != NULL)
	{
		if (tokens->type == PIPE)
		{
			current_cmd->pipe = new_simple_cmd();
			if (current_cmd->pipe == NULL)
				return (free_command(cmd), NULL);
			current_cmd = current_cmd->pipe;
			tokens = tokens->next;
		}
		else if (is_redirection(tokens->type))
		{
			if (handle_redirection(current_cmd, tokens) != 0)
				return (free_command(cmd), NULL);
			tokens = tokens->next->next;
		}
		else
		{
			if (handle_argument(current_cmd, tokens) != 0)
				return (free_command(cmd), NULL);
			tokens = tokens->next;
		}
	}
	return (cmd);
}
