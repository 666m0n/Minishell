/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:30:56 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/15 17:51:45 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_one_token(t_pars_node	*token)
{
	if (token->content)
		free(token->content);
	free(token);
}

void	free_token(t_pars_node *token)
{
	t_pars_node	*tmp;

	while (token != NULL)
	{
		tmp = token;
		token = token->next;
		free_one_token(tmp);
	}
}

int	close_quote_len(char *s, char c)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != c)
		i++;
	return (i + 1);
}
