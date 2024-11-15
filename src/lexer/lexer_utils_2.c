/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:53:16 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/15 19:46:50 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_index_token(t_lexer *tokens)
{
	t_lexer	*current;
	int		i;

	current = tokens;
	i = 0;
	while (current != NULL)
	{
		current->index = i;
		current = current->next;
		i++;
	}
}

void	free_token(t_lexer	*tokens)
{
	t_lexer	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}
