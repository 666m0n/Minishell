/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:30:56 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/30 15:52:11 by sviallon         ###   ########.fr       */
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

