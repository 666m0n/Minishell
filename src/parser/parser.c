/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:43:15 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/08 15:12:30 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_argument(t_simple_cmd *cmd, t_token *token)
{
	char	**new_args;
	int		i;
	int		arg_count;

	if (!cmd->args)
	{
		cmd->args = malloc(sizeof(char *) * 2);
		if (!cmd->args)
			return (EXIT_FAILURE);
		cmd->args[0] = ft_strdup(token->content);
		if (!cmd->args[0])
			return (free(cmd->args), EXIT_FAILURE);
		cmd->args[1] = NULL;
		return (EXIT_SUCCESS);
	}
	arg_count = 0;
	while (cmd->args[arg_count])
		arg_count++;
	new_args = malloc(sizeof(char *) * (arg_count + 2));
	if (!new_args)
		return (EXIT_FAILURE);
	i = 0;
	while (i < arg_count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(token->content);
	if (!new_args[i])
		return (free(new_args), EXIT_FAILURE);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (EXIT_SUCCESS);
}

static int	handle_string_token(t_simple_cmd *cmd, t_token *token)
{
	if (!token->content)
		return (EXIT_FAILURE);
	return (handle_argument(cmd, token));
}

t_command	*parser(t_token *tokens)
{
	t_command		*cmd;
	t_simple_cmd	*current_cmd;
	t_token			*current_token;

	if (!tokens || validate_syntax(tokens) != 0)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->exit_status = 0;
	cmd->cmd = new_simple_cmd();
	if (!cmd->cmd)
		return (free(cmd), NULL);
	current_cmd = cmd->cmd;
	current_token = tokens;
	while (current_token)
	{
		if (current_token->type == T_PIPE)
		{
			current_cmd->pipe = new_simple_cmd();
			if (!current_cmd->pipe)
				return (free_command(cmd), NULL);
			current_cmd = current_cmd->pipe;
			current_token = current_token->next;
		}
		else if (is_redirection(current_token->type))
		{
			if (handle_redirection(current_cmd, current_token) != 0)
				return (free_command(cmd), NULL);
			current_token = current_token->next->next;
		}
		else if (current_token->type == T_STRING
			|| current_token->type == T_SQUOTE
			|| current_token->type == T_DQUOTE)
		{
			if (handle_string_token(current_cmd, current_token) != 0)
				return (free_command(cmd), NULL);
			current_token = current_token->next;
		}
		else
			current_token = current_token->next;
	}
	return (cmd);
}
