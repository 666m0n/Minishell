/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:33:18 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/14 10:15:08 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	lexer_init_node(t_pars_node *new_node, t_token type, char *content)
{
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->content = ft_strdup(content);
	new_node->type = type;
	new_node->index = 0;
}

void	lexer_new_node(t_token type, char *content, t_pars_node **token)
{
	t_pars_node	*new_node;
	t_pars_node	*last;

	if (!content || !token)
		return ;
	new_node = ft_calloc(1, sizeof(t_pars_node));
	if (!new_node)
		return ;
	lexer_init_node(new_node, type, content);
	if (!*token)
	{
		*token = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
	}
	else
	{
		last = lexer_last_node(*token);
		last->next = new_node;
		new_node->prev = last;
	}
}

t_pars_node	*lexer_last_node(t_pars_node *token)
{
	while (token->next != NULL)
		token = token->next;
	return (token);
}
