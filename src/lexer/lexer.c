/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:17:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/14 11:55:19 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// rassemble les infos pour le token et creer le node
t_pars_node	*lexer_create(char *str, t_ctx *ctx)
{
	t_pars_node	*new;
	t_token		type;
	int			len;

	new = NULL;
	type = lex_get_type(str);
	len = lex_get_len(str, type);
}

void	lexer(char *line, t_ctx *ctx)
{
	t_pars_node	*token;
	t_pars_node	*tmp;
	int			i;

	i = 0;
	token = NULL;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			tmp = lexer_create(&(line[i]), ctx);
		}
		else
			i++;
	}
}
