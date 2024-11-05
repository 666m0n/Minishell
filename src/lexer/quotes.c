/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:19:34 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/05 16:48:29 by sviallon         ###   ########.fr       */
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

int	is_in_dquote(const char *str, int pos)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (i < pos)
	{
		if (str[i] == '"' && !is_in_squote(str, i))
			in_quote = !in_quote;
		i++;
	}
	return (in_quote);
}

int	is_char_escaped(const char *str, int pos)
{
	if (is_in_squote(str, pos))
		return (1);
	if (is_in_dquote(str, pos) && str[pos] != '"' && str[pos] != '$')
		return (1);
	return (0);
}


// Helper pour identifier les caractères valides dans un nom de variable
int	is_valid_var_char(char c, int is_first_char)
{
	if (is_first_char)
	{
		if (ft_isalpha(c) || c == '_')
			return (1);
		return (0);
	}
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	get_var_len(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '?' || ft_isdigit(str[0]))
		return (1);
	while (str[i] && is_valid_var_char(str[i], i == 0))
		i++;
	return (i);
}

char	*handle_var_expansion(const char *str, t_ctx *ctx, int *i)
{
	char	*var_name;
	char	*value;
	char	*result;
	int		var_len;

	(*i)++; // Skip $
	if (!str[*i] || str[*i] == ' ' || str[*i] == '\t')
	{
		(*i)--; // Reculer pour que le $ soit traité comme un caractère normal
		return (ft_strdup("$"));
	}
	if (str[*i] == '$')
	{
		(*i)++;
		return (ft_strdup("$$"));
	}
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(ctx->exit_code));
	}
	if (ft_isdigit(str[*i]))
	{
		result = ft_strdup("");
		if (str[*i] == '0')
		{
			result = ft_strjoin_free(result, ft_strdup("minishell"));
			(*i)++; // Skip le 0
			while (str[*i] && str[*i] != ' ' && str[*i] != '\''
				&& str[*i] != '"' && str[*i] != '$')
			{
				char *tmp = ft_chartostr(str[(*i)++]);
				result = ft_strjoin_free(result, tmp);
			}
			(*i)--;
			return (result);
		}
		(*i)++; // Skip le premier chiffre
		while (str[*i] && ft_isdigit(str[*i]))
		{
			char *tmp = ft_chartostr(str[(*i)++]);
			result = ft_strjoin_free(result, tmp);
		}
		(*i)--;
		return (result);
	}
	var_len = get_var_len(str + *i);
	if (var_len == 0)
	{
		if (str[*i])
		{
			result = ft_chartostr('$');
			result = ft_strjoin_free(result, ft_chartostr(str[*i]));
			return (result);
		}
		return (ft_strdup("$"));
	}
	var_name = ft_substr(str, *i, var_len);
	if (!is_valid_var_char(var_name[0], 1))
	{
		free(var_name);
		result = ft_chartostr('$');
		result = ft_strjoin_free(result, ft_chartostr(str[*i]));
		return (result);
	}
	value = get_env_value(ctx->envp, var_name);
	free(var_name);
	*i += var_len - 1;
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char *expand_token(char *str, t_ctx *ctx, t_token type)
{
    char    *result;
    char    *tmp;
    int     i;
    int     in_dquote;

    if (!str)
        return (NULL);

    // Si c'est une S_QUOTE seule, on retire juste les quotes
    if (type == S_QUOTE && str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
    {
        size_t len = ft_strlen(str);
        if (len >= 2)
            return (ft_strndup(str + 1, len - 2));
    }

    result = ft_strdup("");
    if (!result)
        return (NULL);

    i = 0;
    in_dquote = 0;
    while (str[i])
    {
        if (str[i] == '"' && !is_in_squote(str, i))
            in_dquote = !in_dquote;
        else if (str[i] == '$' && !is_in_squote(str, i))
        {
            tmp = handle_var_expansion(str, ctx, &i);
            result = ft_strjoin_free(result, tmp);
        }
        else if (str[i] != '\'' || type == S_QUOTE)
        {
            if (str[i] != '"' || type == D_QUOTE || is_in_squote(str, i))
            {
                tmp = ft_chartostr(str[i]);
                result = ft_strjoin_free(result, tmp);
            }
        }
        i++;
    }

    return (result);
}

/* // Expand uniquement les variables hors quotes simples
char	*expand_token(char *str, t_ctx *ctx, t_token type)
{
	char	*unquoted;
	char	*expanded;

	unquoted = strip_quotes(str);
	if (!unquoted)
		return (NULL);
	if (type == S_QUOTE)
		return (unquoted);
	if (ft_strchr(unquoted, '$'))
	{
		expanded = expand_variables(unquoted, ctx->envp, ctx->exit_code);
		free(unquoted);
		return (expanded);
	}
	return (unquoted);
} */

int	process_token_content(t_pars_node *token, t_ctx *ctx)
{
	char	*processed;

	if (!token || !token->content)
		return (0);
	processed = expand_token(token->content, ctx, token->type);
	if (!processed)
		return (EXIT_FAILURE);
	free(token->content);
	token->content = processed;
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
