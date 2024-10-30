/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:19:34 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/30 11:46:34 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Retire les quotes d'une chaine 
char	*remove_quotes(char *str)
{
	char	*result;
	size_t	new_len;

	if (!str)
		return (NULL);

	new_len = get_unquoted_len(str);
	result = malloc(sizeof(char) * (new_len + 1));
	if (!result)
		return (NULL);

	copy_unquoted_content(result, str);
	return (result);
}

// Expand les variables d'env dans une chaine entre double quotes
char	*expand_within_dquotes(char *str, t_ctx *ctx)
{
	char	*expanded;
	char	*result;

	expanded = expand_variables(str, ctx->envp, ctx->exit_code);
	if (!expanded)
		return (NULL);
	result = remove_quotes(expanded);
	free(expanded);

	return (result);
}

int	process_token_content(t_pars_node *token, t_ctx *ctx)
{
	char	*processed;

	if (!token || !token->content)
		return (0);

	if (token->type == S_QUOTE)
	{
		processed = remove_quotes(token->content);
		if (!processed)
			return (1);
		free(token->content);
		token->content = processed;
		token->type = STRING;
	}
	else if (token->type == D_QUOTE)
	{
		processed = expand_within_dquotes(token->content, ctx);
		if (!processed)
			return (1);
		free(token->content);
		token->content = processed;
		token->type = STRING;
	}
	return (0);
}

int	process_quotes(t_pars_node *tokens, t_ctx *ctx)
{
	t_pars_node	*current;

	current = tokens;
	while (current)
	{
		if (process_token_content(current, ctx) != 0)
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (SUCCESS);
}
