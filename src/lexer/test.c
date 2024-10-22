/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42Paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:52:49 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/22 22:55:09 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_pars_node *tokens)
{
	t_pars_node	*current = tokens;
	int			i = 1;

	while (current)
	{
		printf("Token %d:\n", i++);
		printf("  Content: '%s'\n", current->content);
		printf("  Type: ");
		switch(current->type)
		{
			case STRING: printf("STRING\n"); break;
			case D_QUOTE: printf("D_QUOTE\n"); break;
			case S_QUOTE: printf("S_QUOTE\n"); break;
			case PIPE: printf("PIPE\n"); break;
			case INFILE: printf("INFILE\n"); break;
			case OUTFILE: printf("OUTFILE\n"); break;
			case HEREDOC: printf("HEREDOC\n"); break;
			case APPEND: printf("APPEND\n"); break;
			case ESPACE: printf("ESPACE\n"); break;
		}
		printf("\n");
		current = current->next;
	}
}
