/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:17:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/08 15:22:43 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	should_merge_tokens(t_token *current)
{
	if (!current || !current->next)
		return (0);
	if (current->space_after)
		return (0);
	return (1);
}

static t_token	*merge_adjacent_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;
	char	*merged;

	if (!tokens)
		return (NULL);
	current = tokens;
	while (current && current->next)
	{
		if (!should_merge_tokens(current))
		{
			current = current->next;
			continue ;
		}
		next = current->next;
		merged = ft_strjoin(current->content, next->content);
		if (!merged)
			return (NULL);
		free(current->content);
		current->content = merged;
		current->next = next->next;
		if (next->next)
			next->next->prev = current;
		current->type = T_STRING;
		current->space_after = next->space_after;
		free(next->content);
		free(next);
	}
	return (tokens);
}

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
	if (type == T_PIPE || type == T_INPUT || type == T_OUTPUT)
		return (1);
	if (type == T_APPEND || type == T_HEREDOC)
		return (2);
	return (get_token_str_len(s));
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
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		tmp = tokenize(&input[i]);
		if (!tmp)
		{
			free_token(lexer.head);
			return (NULL);
		}
		add_token(&lexer, tmp);
		i += add_str_len(tmp->content, tmp->type);
		while (i < lexer.len && ft_isspace(input[i]))
			i++;
	}
	if (!expand_variables(lexer.head, lexer.env, lexer.last_exit))
	{
		free_token(lexer.head);
		return (NULL);
	}
	return (merge_adjacent_tokens(lexer.head));
}
