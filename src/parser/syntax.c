/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:58:12 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/30 10:19:05 by sviallon         ###   ########.fr       */
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
static int	check_redirection(t_pars_node *token)
{
	if (!token->next)
		return (syntax_error("newline"));
	if (token->next->type != STRING)
		return (syntax_error(token->next->content));
	return (0);
}

// Vérifie qu'un pipe est correctement formé
static int	check_pipe(t_pars_node *token)
{
	if (!token->next)
		return (syntax_error("|"));
	if (token->next->type == PIPE)
		return (syntax_error("|"));
	return (0);
}

int	validate_syntax(t_pars_node *tokens)
{
	t_pars_node	*current;
	int			cmd_found;

	if (!tokens)
		return (0);
	if (tokens->type == PIPE)
		return (syntax_error("|"));

	current = tokens;
	cmd_found = 0;

	while (current)
	{
		if (is_redirection(current->type))
		{
			if (check_redirection(current) != 0)
				return (1);
			current = current->next;
		}
		else if (current->type == PIPE)
		{
			if (!cmd_found)
				return (syntax_error("|"));
			if (check_pipe(current) != 0)
				return (1);
			cmd_found = 0;
		}
		else if (current->type == STRING)
			cmd_found = 1;

		current = current->next;
	}
	return (0);
}