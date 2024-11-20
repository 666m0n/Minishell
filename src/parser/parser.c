/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:43:15 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/20 12:57:39 by sviallon         ###   ########.fr       */
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

t_cmd	*parser(t_lexer *tokens, t_ctx *data)
{
	t_cmd			*head;
	t_cmd			*current_cmd;
	t_lexer			*tmp;

	head = NULL;
	current_cmd = NULL;
	tmp = tokens;
	init_cmd(&head, &current_cmd);
	handle_dollar(tmp, data);
	process_pars(current_cmd, tmp, data);
	return (head);
}
