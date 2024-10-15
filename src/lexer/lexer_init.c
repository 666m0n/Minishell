/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:33:18 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/15 11:24:20 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_pars_node	*lexer_new_token(char *content, int n, t_token type, t_ctx *ctx)
{
	t_pars_node	*token;
	char		*new;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	new = ft_strndup(content, n);
	if (!new)
	{
		free(token);
		return (NULL);
	}
	token->content = new;
	token->type = type;
	token->ctx = ctx;
	token->next = NULL;
	return (token);
}

t_pars_node	*lex_last_tok(t_pars_node *token)
{
	while (token->next != NULL)
		token = token->next;
	return (token);
}

int	tok_add_back(t_pars_node **head, t_pars_node *new)
{
	if (new == NULL)
		return (1);
	if (*head == NULL)
		*head = new;
	else
		lex_last_tok(*head)->next = new;
	return (0);
}
