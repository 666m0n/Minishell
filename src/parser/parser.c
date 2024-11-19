/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:43:15 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/19 14:54:08 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *var_name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->id, var_name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	free_double(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	exit_error(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

static void	init_cmd(t_cmd **head, t_cmd **curr)
{
	*head = ft_calloc(sizeof(t_cmd), 1);
	*curr = *head;
	(*curr)->next = NULL;
	(*curr)->prev = NULL;
	(*curr)->index = 0;
}

t_cmd	*parser(t_lexer **tokens, t_ctx data)
{
	int	error;

	error = 0;
	if (handle_quotes(*tokens) != 0)
		error = 1;
	else if (expand_and_quotes(*tokens) != 0)
		error = 1;
	else if (remove_null(tokens) != 0)
		error = 1;
	else if (check_all_null(*tokens) != 0)
		error = 1;
	else if (handle_cmd(*tokens) != 0)
		error = 1;
	else if (handle_heredoc(*tokens) != 0)
		error = 1;

}
