/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:17:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/30 12:45:13 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// rassemble les infos pour le token et creer le node
t_pars_node	*lexer_create(char *str, t_ctx *ctx)
{
	t_pars_node	*new;
	t_token		type;
	int			len;

	type = lex_get_type(str);
	len = lex_get_len(str, type);
	new = lexer_new_token(str, len, type, ctx);
	return (new);
}

//fonction principale pour tokenisation
t_pars_node	*lexer(char *line, t_ctx *ctx)
{
	t_pars_node	*tokens;
	t_pars_node	*temp;
	int			i;

	i = 0;
	tokens = NULL;
	if (!handle_quotes(line))
	{
		while (line[i])
		{
			if (line[i] != ' ' && line[i] != '\t')
			{
				temp = lexer_create(&(line[i]), ctx);
				if (temp == NULL)
					return (free_token(tokens), NULL);
				tok_add_back(&(tokens), temp);
				i += ft_strlen(temp->content);
			}
			else
				i++;
		}
		if (process_quotes(tokens, ctx) != 0)
			return (free_token(tokens), NULL);
	}
	return (tokens);
}
