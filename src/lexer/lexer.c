/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:17:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/07 18:36:25 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(char *s)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		if (s[i] == '\"' && !s_quote)
			d_quote = !d_quote;
		i++;
	}
	if (d_quote % 2 != 0 || s_quote % 2 != 0)
		return (printf("%s", QUOTE_ERROR), 1);
	return (0);
}

int	add_str_len(char *s, t_token_type type)
{
	int	len;

	len = ft_strlen(s);
	if (type == T_SQUOTE || type == T_DQUOTE)
		len += 2;
	return (len);
}

void	init_lexer(t_lexer *lexer, char *input, t_env *env, int last_exit)
{
	lexer->input = input;
	lexer->pos = 0;
	lexer->len = ft_strlen(input);
	lexer->head = NULL;
	lexer->current = NULL;
	lexer->env = env;
	lexer->last_exit = last_exit;
}

t_token	*lexer(char *input, t_env *env, int last_exit)
{
	t_lexer	lexer;
	t_token	*tmp;
	size_t	i;

	init_lexer(&lexer, input, env, last_exit);
	if (handle_quotes(input))
		return (NULL);
	i = 0;
	while (i < lexer.len)
	{
		tmp = tokenize(&input[i]);
		if (!tmp)
		{
			free_token(lexer.head);
			return (NULL);
		}
		add_token(&lexer, tmp);
		i += add_str_len(tmp->content, tmp->type);
	}
	if (!expand_variables(lexer.head, &lexer))
	{
		free_token(lexer.head)
		return (NULL);
	}
	return (lexer.head);
}
