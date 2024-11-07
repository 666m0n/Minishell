/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:52:49 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/07 11:04:01 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//test lexer
void	print_tokens(t_token *tokens)
{
	t_token		*current = tokens;
	int			i = 1;

	printf("\n=== TOKENS ===\n");
	while (current)
	{
		printf("Token %d:\n", i++);
		printf("  Content: '%s'\n", current->content);
		printf("  Type: ");
		switch(current->type)
		{
			case T_STRING:    printf("STRING\n"); break;
			case T_APPEND:    printf("APPEND\n"); break;
			case T_INPUT:    printf("INFILE\n"); break;
			case T_OUTPUT:   printf("OUTFILE\n"); break;
			case T_HEREDOC:   printf("HEREDOC\n"); break;
			case T_DQUOTE:   printf("D_QUOTE\n"); break;
			case T_SQUOTE:   printf("S_QUOTE\n"); break;
			case T_PIPE:      printf("PIPE\n"); break;
			case T_EOF:       printf("EOF\n"); break;
			default:        printf("UNKNOWN\n"); break;
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
			if (redir->type == T_INPUT)
				printf("< %s\n", redir->file);
			else if (redir->type == T_OUTPUT)
				printf("> %s\n", redir->file);
			else if (redir->type == T_APPEND)
				printf(">> %s\n", redir->file);
			else if (redir->type == T_HEREDOC)
				printf("<< %s\n", redir->file);
			redir = redir->next;
		}
		if (current->pipe != NULL)
			printf("  | PIPE |\n");
		current = current->pipe;
	}
}
