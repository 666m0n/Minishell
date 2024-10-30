/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42Paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:58:12 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/30 08:49:46 by sviallon         ###   ########.fr       */
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
	// Une redirection doit être suivie d'un token
	if (!token->next)
		return (syntax_error("newline"));

	// Le token suivant une redirection doit être un STRING
	if (token->next->type != STRING)
		return (syntax_error(token->next->content));

	return (0);
}

// Vérifie qu'un pipe est correctement formé
static int	check_pipe(t_pars_node *token)
{
	// Un pipe ne peut pas être le dernier token
	if (!token->next)
		return (syntax_error("|"));

	// Un pipe ne peut pas être suivi d'un autre pipe
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
		// Vérifie les redirections
		if (is_redirection_token(current->type))
		{
			if (check_redirection(current) != 0)
				return (1);
			current = current->next; // Skip le nom du fichier
		}
		// Vérifie les pipes
		else if (current->type == PIPE)
		{
			if (!cmd_found)
				return (syntax_error("|"));
			if (check_pipe(current) != 0)
				return (1);
			cmd_found = 0;
		}
		// Si on trouve un token qui n'est pas une redirection ou un pipe,
		// on considère qu'on a trouvé une commande
		else if (current->type == STRING)
			cmd_found = 1;

		current = current->next;
	}

	return (0);
}
