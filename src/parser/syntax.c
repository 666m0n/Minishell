/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:58:12 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/06 15:10:45 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(const char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

// Vérifie qu'une redirection est correctement formée (suivie d'un fichier)
static int	check_redirection(t_token *token)
{
	if (!token->next)
		return (syntax_error("newline"));
	if (token->next->type != T_STRING)
		return (syntax_error(token->next->content));
	return (0);
}

// Vérifie qu'un pipe est correctement formé
static int	check_pipe(t_token *token)
{
	if (!token->next)
		return (syntax_error("|"));
	if (token->next->type == T_PIPE)
		return (syntax_error("|"));
	return (0);
}

int	validate_syntax(t_token *tokens)
{
	int			cmd_found;

	if (!tokens)
		return (0);
	if (tokens->type == T_PIPE)
		return (syntax_error("|"));
	cmd_found = 0;
	while (tokens)
	{
		if (is_redirection(tokens->type))
		{
			if (check_redirection(tokens) != 0)
				return (1);
			tokens = tokens->next;
		}
		else if (tokens->type == T_PIPE)
		{
			if (!cmd_found)
				return (syntax_error("|"));
			if (check_pipe(tokens) != 0)
				return (1);
			cmd_found = 0;
		}
		else if (tokens->type == T_STRING)

			cmd_found = 1;

		tokens = tokens->next;
	}
	return (0);
}
