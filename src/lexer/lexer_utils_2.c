/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:53:16 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/12 19:12:42 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	space_handler(t_lexer **tokens, char **str)
{
	char	*new;

	new = malloc(sizeof(char) * 2);
	if (!new)
		return ;
	new[0] = **str;
	new[1] = '\0';
	if (ft_isspace(**str))
	{
		create_token(T_SPACE, new, tokens);
		while (**str && ft_isspace(**str))
			(*str)++;
	}
	free(new);
}

void	add_index_token(t_lexer *tokens)
{
	t_lexer	*current;
	int		i;

	current = tokens;
	i = 0;
	while (current != NULL)
	{
		current->index = i;
		current = current->next;
		i++;
	}
}

void	free_token(t_lexer	*tokens)
{
	t_lexer	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

static char	*trim_quotes(char *str)
{
	char	*trimmed;
	size_t	len;
	size_t	start;
	size_t	end;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	start = 0;
	while (str[start] && (str[start] == '\'' || str[start] == '"'))
		start++;
	end = len;
	while (end > start && (str[end - 1] == '\'' || str[end - 1] == '"'))
		end--;
	trimmed = ft_substr(str, start, end - start);
	return (trimmed);
}

void	check_cmd_quotes(t_lexer *tokens)
{
	t_lexer	*current;
	char	*trimmed;

	current = tokens;
	while (current)
	{
		if (current->type == T_CMD)
		{
			trimmed = trim_quotes(current->content);
			free(current->content);
			current->content = trimmed;
		}
		current = current->next;
	}
}
