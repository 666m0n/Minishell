/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:12:54 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/26 13:20:30 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_syntax	*create_syntax_node(t_lexer *token)
{
	t_syntax	*new;

	new = ft_calloc(1, sizeof(t_syntax));
	if (!new)
		return (NULL);
	new->content = ft_strdup(token->content);
	if (!new->content)
	{
		free(new);
		return (NULL);
	}
	new->type = token->type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static void	add_syntax_node(t_syntax **lst, t_syntax *new)
{
	t_syntax	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

void	free_syntax_list(t_syntax *list)
{
	t_syntax	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

t_syntax	*create_syntax_list(t_lexer *tokens)
{
	t_syntax	*syntax_list;
	t_lexer		*curr;
	t_syntax	*new_node;

	syntax_list = NULL;
	curr = tokens;
	while (curr)
	{
		if (curr->type != T_SPACE)
		{
			new_node = create_syntax_node(curr);
			if (!new_node)
			{
				free_syntax_list(syntax_list);
				return (NULL);
			}
			add_syntax_node(&syntax_list, new_node);
		}
		curr = curr->next;
	}
	return (syntax_list);
}
