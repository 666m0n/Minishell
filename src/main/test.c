/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:52:49 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/15 19:28:22 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_lexer *tokens)
{
	t_lexer		*current;
	int			i;

	i = 1;
	current = tokens;
	printf("\n=== TOKENS ===\n");
	while (current)
	{
		printf("Token %d:\n", i++);
		printf("  Content: '%s'\n", current->content);
		printf("  Type: ");
		switch (current->type)
		{
			case T_STRING:	printf("STRING\n"); break ;
			case T_APPEND:	printf("APPEND\n"); break ;
			case T_REDIRIN:	printf("REDIRIN\n"); break ;
			case T_REDIROUT:	printf("REDIROUT\n"); break ;
			case T_HEREDOC:	printf("HEREDOC\n"); break ;
			case T_DQUOTE:	printf("DQUOTE\n"); break ;
			case T_SQUOTE:	printf("SQUOTE\n"); break ;
			case T_PIPE:	printf("PIPE\n"); break ;
			case T_SPACE:	printf("SPACE\n"); break ;
			case T_CMD:	printf("CMD\n"); break ;
			case T_OPTIONS:	printf("OPTIONS\n"); break ;
			case T_AMPERSAND:	printf("AMPERSAND\n"); break ;
			default:	printf("UNKNOWN\n"); break ;
		}
		current = current->next;
	}
	printf("=============\n\n");
}

void	print_command(t_cmd *cmd)
{
	t_lexer		*redir;
	int			i;

	while (cmd)
	{
		printf("Command %d:\n", cmd->index);
		i = 0;
		if (cmd->args)
		{
			printf("  Arguments:\n");
			while (cmd->args[i])
				printf("    Arg[%d]: %s\n", i++, cmd->args[i]);
		}
		redir = cmd->redirections;
		if (redir)
			printf("  Redirections:\n");
		while (redir)
		{
			printf("    Type: ");
			if (redir->type == T_REDIRIN)
				printf("< %s\n", redir->content);
			else if (redir->type == T_REDIROUT)
				printf("> %s\n", redir->content);
			else if (redir->type == T_APPEND)
				printf(">> %s\n", redir->content);
			else if (redir->type == T_HEREDOC)
				printf("<< %s\n", redir->content);
			redir = redir->next;
		}
		cmd = cmd->next;
		if (cmd)
			printf("  | PIPE |\n");
	}
}
