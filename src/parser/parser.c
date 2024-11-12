/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:43:15 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/12 15:46:13 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_cmd(t_cmd **head, t_cmd **curr)
{
	*head = ft_calloc(sizeof(t_cmd), 1);
	*curr = *head;
	(*curr)->next = NULL;
	(*curr)->prev = NULL;
	(*curr)->index = 0;
}

t_cmd	*parser(t_lexer *tokens, t_ctx *data)
{
	t_cmd			*head;
	t_cmd			*current_cmd;
	t_token			*tmp;

	head = NULL;
	current_cmd = NULL;
	tmp = tokens;
	init_cmd(&head, &current_cmd);
	handle_dollar(tmp, data);
	process_pars(current_cmd, tmp, data);
	return (head);
}
