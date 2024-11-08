/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:19:34 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/08 15:32:39 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_token_content(t_token *token, const char *s, int len)
{
	char	*tmp;

	token->content = ft_strndup(s, len);
	if (!token->content)
		exit_error("malloc failed");
	if (token->type == T_SQUOTE)
	{
		tmp = ft_strndup(token->content + 1, ft_strlen(token->content) - 2);
		if (!tmp)
			exit_error("malloc failed");
		free(token->content);
		token->content = tmp;
	}
	else if (token->type == T_DQUOTE)
	{
		tmp = ft_strndup(token->content + 1, ft_strlen(token->content) - 2);
		if (!tmp)
			exit_error("malloc failed");
		free(token->content);
		token->content = tmp;
	}
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	if (len > n)
		len = n;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	free_token(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

char	*copy_str(const char *src, char *to_ret, int len, t_token_type type)
{
	char	*tmp;

	to_ret = ft_strndup(src, len);
	if (!to_ret)
		return (NULL);
	if (type == T_SQUOTE)
	{
		tmp = ft_strtrim(to_ret, "'");
		if (!tmp)
			return (NULL);
		free(to_ret);
		to_ret = tmp;
	}
	else if (type == T_DQUOTE)
	{
		tmp = ft_strtrim(to_ret, "\"");
		if (!tmp)
			return (NULL);
		free(to_ret);
		to_ret = tmp;
	}
	return (to_ret);
}

t_token	*create_token(const char *s, int len, t_token_type type)
{
	t_token	*node;

	if (!s || len < 0)
		return (NULL);
	node = malloc(sizeof(t_token));
	if (!node)
		exit_error("malloc failed");
	node->type = type;
	node->expandable = (type != T_SQUOTE);
	handle_token_content(node, s, len);
	node->next = NULL;
	node->prev = NULL;
	node->space_after = 0;
	return (node);
}

void	add_token(t_lexer *lexer, t_token *new_node)
{
	char	*input;
	size_t	pos;

	if (!new_node)
		return ;
	pos = lexer->pos + ft_strlen(new_node->content);
	input = lexer->input;
	new_node->space_after = (input[pos] == ' ' || input[pos] == '\t');
	if (!lexer->head)
	{
		lexer->head = new_node;
		lexer->current = new_node;
	}
	else
	{
		lexer->current->next = new_node;
		new_node->prev = lexer->current;
		lexer->current = new_node;
	}
}
