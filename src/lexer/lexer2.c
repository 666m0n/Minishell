/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:19:34 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/07 11:39:01 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	node = malloc(sizeof(t_token));
	if (!node)
		exit_error("malloc token structure failed");
	node->type = type;
	node->expandable = (type != T_SQUOTE);
	node->content = copy_str(s, node->content, len, type);
	if (!node->content)
	{
		free(node);
		exit_error("strdup input token failed");
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_token(t_lexer *lexer, t_token *new_node)
{
	if (!new_node)
		return ;
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
