/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:19:34 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/30 17:19:22 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Vérifie si un caractère est dans une quote simple
int	is_in_squote(const char *str, int pos)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (i < pos)
	{
		if (str[i] == '\'')
			in_quote = !in_quote;
		i++;
	}
	return (in_quote);
}

// Expand uniquement les variables hors quotes simples
char	*expand_token(char *str, t_ctx *ctx, t_token type)
{
	int		i;
	int		in_squote;
	char	*expanded;
	char	*tmp;

	if (!ft_strchr(str, '$'))
		return (ft_strdup(str));
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	i = 0;
	while (str[i])
	{
		in_squote = is_in_squote(str, i);
		if (str[i] == '$' && !in_squote)
		{
			tmp = expand_variables(&str[i], ctx->envp, ctx->exit_code);
			if (!tmp)
			{
				free(expanded);
				return (NULL);
			}
			expanded = ft_strjoin_free(expanded, tmp);
			while (str[i] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
				i++;
		}
		else
		{
			if (type == D_QUOTE && (str[i] == '"'))
			{
				i++;
				continue ;
			}
			tmp = ft_chartostr(str[i]);
			expanded = ft_strjoin_free(expanded, tmp);
		}
		i++;
	}
	return (expanded);
}

int	process_token_content(t_pars_node *token, t_ctx *ctx, t_token type)
{
	char	*processed;

	if (!token || !token->content)
		return (0);
	processed = expand_token(token->content, ctx, type);
	if (!processed)
		return (EXIT_FAILURE);
	free(token->content);
	token->content = processed;
	return (0);
}

int	process_quotes(t_pars_node *tokens, t_ctx *ctx, t_token type)
{
	t_pars_node	*current;

	current = tokens;
	while (current)
	{
		if (process_token_content(current, ctx, type) != 0)
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (SUCCESS);
}
