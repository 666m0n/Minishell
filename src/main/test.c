/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:52:49 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/23 14:10:55 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//test lexer
void	rint_tokens(t_pars_node *tokens)
{
	t_pars_node	*current = tokens;
	int			i = 1;

	printf("\n=== TOKENS ===\n");
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
		current = current->next;
	}
	printf("=============\n\n");
}

//test parsing
void	print_command(t_command *cmd)
{
	t_simple_cmd *current;
	t_redirection *redir;
	int i;

	current = cmd->cmd;
	while (current != NULL)
	{
		printf("Command:\n");
		i = 0;
		if (current->args != NULL)
		{
			while (current->args[i] != NULL)
			{
				printf("  Arg[%d]: %s\n", i, current->args[i]);
				i++;
			}
		}
		redir = current->redirections;
		while (redir != NULL)
		{
			printf("  Redirection: ");
			if (redir->type == INFILE)
				printf("< %s\n", redir->file);
			else if (redir->type == OUTFILE)
				printf("> %s\n", redir->file);
			else if (redir->type == APPEND)
				printf(">> %s\n", redir->file);
			else if (redir->type == HEREDOC)
				printf("<< %s\n", redir->file);
			redir = redir->next;
		}
		if (current->pipe != NULL)
			printf("  | PIPE |\n");
		current = current->pipe;
	}
}
