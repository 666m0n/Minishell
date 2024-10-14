/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:33:18 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/14 15:27:45 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	lexer_init_node(t_pars_node *new_node, t_token type, char *content,
	int n)
{
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->content = ft_strndup(content, n);
	new_node->type = type;
}

t_pars_node	*lexer_new_node(t_token type, char *content, int len,
	t_pars_node **token)
{
	t_pars_node	*new_node;
	t_pars_node	*last;

	if (!content || !token)
		return (NULL);
	new_node = ft_calloc(1, sizeof(t_pars_node));
	if (!new_node)
		return (free(new_node), NULL);
	lexer_init_node(new_node, type, content, len);
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
	return (new_node);
}

t_pars_node	*lexer_last_node(t_pars_node *token)
{
	while (token->next != NULL)
		token = token->next;
	return (token);
}
