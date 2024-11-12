/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:53:16 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/12 11:48:56 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_index_to_token(t_lexer *tokens)
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
