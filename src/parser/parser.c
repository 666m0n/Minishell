/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:43:15 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/08 13:44:06 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token *token)

{
	int	count;

	count = 0;
	while (token && token->type != T_PIPE)
	{
		if (token->type == T_STRING)
			count++;
		else if (is_redirection(token->type))
			token = token->next;
		token = token->next;
	}
	return (count);
}

static char	**create_args_array(t_token *token, int arg_count)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (token && token->type != T_PIPE && i < arg_count)
	{
		if (token->type == T_STRING)
		{
			args[i] = ft_strdup(token->content);
			if (!args[i])
			{
				while (--i >= 0)
					free(args[i]);
				free(args);
				return (NULL);
			}
			i++;
		}
		else if (is_redirection(token->type))
			token = token->next;
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

static int	process_command(t_simple_cmd *cmd, t_token *token)
{
	int		arg_count;

	arg_count = count_args(token);
	if (arg_count > 0)
	{
		cmd->args = create_args_array(token, arg_count);
		if (!cmd->args)
			return (-1);
	}
	return (0);
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
		else
		{
			if (process_command(current_cmd, current_token) != 0)
				return (free_command(cmd), NULL);
			while (current_token && current_token->type != T_PIPE)
				current_token = current_token->next;
		}
	}
	return (cmd);
}
