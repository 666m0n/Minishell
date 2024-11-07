/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:43:15 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/07 15:21:07 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_string_token(t_simple_cmd *cmd, t_token *token)
{}

int	handle_argument(t_simple_cmd *cmd, t_token *tokens)
{
	char	**new_args;
	int		i;
	int		j;

	i = 0;
	if (cmd->args != NULL)
		while (cmd->args[i] != NULL)
			i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (EXIT_FAILURE);
	j = -1;
	while (++j < i)
	{
		new_args[j] = ft_strdup(cmd->args[j]);
		if (!new_args[j])
		{
			while (--j >= 0)
				free(new_args[j]);
			free(new_args);
			return (EXIT_FAILURE);
		}
	}
	new_args[i] = ft_strdup(tokens->content);
	if (!new_args[i])
	{
		while (--i >= 0)
			free(new_args[i]);
		free(new_args);
		return (EXIT_FAILURE);
	}
	new_args[i + 1] = NULL;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	cmd->args = new_args;
	return (0);
}

t_command	*parser(t_token *tokens)
{
	t_command		*cmd;
	t_simple_cmd	*current_cmd;

	if (!tokens)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (cmd == NULL)
		return (NULL);
	cmd->exit_status = 0;
	cmd->cmd = new_simple_cmd();
	if (!cmd->cmd)
	{
		free(cmd);
		return (NULL);
	}
	current_cmd = cmd->cmd;
	while (tokens != NULL)
	{
		if (tokens->type == T_PIPE)
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
		else if (tokens->type == T_STRING || tokens->type == T_SQUOTE
			|| tokens->type == T_DQUOTE)
		{
			if (handle_string_token(current_cmd, tokens))
				return (NULL);
			tokens = tokens->next;
		}
		else
			tokens = tokens->next;
	}
	return (cmd);
}
