/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:17:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/16 13:23:55 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *s)
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
		else if (s[i] == '\"' && !s_quote)
			d_quote = !d_quote;
		i++;
	}
	if (d_quote % 2 != 0 || s_quote % 2 != 0)
		return (printf("%s", QUOTE_ERROR), 1);
	return (0);
}

static int	check_tokens(char **str, t_lexer **tokens)
{
	char	unknown[2];

	if (**str == '|')
		return (pipe_handler(tokens, str), 1);
	else if (ft_strchr(IS_REDIRECTION, **str))
		return (redir_handler(tokens, str), 1);
	else if (**str == '\'' || **str == '"')
		return (quotes_handler(tokens, str), 1);
	else if (**str == '&')
	{
		if (*(*str + 1) == '&')
			return (create_token(T_AMPERSAND, "&&", tokens),
				(*str) += 2, 1);
		else
			return (create_token(T_AMPERSAND, "&", tokens), (*str)++, 1);
	}
	else if (!strchr(IS_TOKEN, **str) && !ft_isspace(**str))
	{
		unknown[0] = **str;
		unknown[1] = '\0';
		return (create_token(T_UNKNOWN, unknown, tokens), (*str)++, 1);
	}
	return (0);
}

static void	check_cmd(char **str, t_lexer **tokens)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = ft_strdup(*str);
	if (!cmd)
		return ;
	while (**str && !ft_isspace(**str) && !ft_strchr(IS_TOKEN, **str))
	{
		(*str)++;
		i++;
	}
	cmd[i] = '\0';
	create_token(T_CMD, cmd, tokens);
	free(cmd);
}

void	check_options(char **str, t_lexer **tokens)
{
	int		i;
	char	*options;

	i = 0;
	options = ft_strdup(*str);
	if (!options)
		return ;
	while (**str && !ft_isspace(**str) && !ft_strchr(IS_TOKEN, **str))
	{
		if (ft_strchr(IS_TOKEN, **str))
			break ;
		(*str)++;
		i++;
	}
	options[i] = '\0';
	create_token(T_OPTIONS, options, tokens);
	free(options);
}

t_lexer	*lexer(char *input)
{
	t_lexer	*tokens;

	tokens = NULL;
	while (*input && ft_isspace(*input))
		input++;
	if (!check_quotes(input))
	{
		while (*input)
		{
			if (ft_isspace(*input))
				space_handler(&tokens, &input);
			else if (*input && ft_isascii(*input)
				&& !ft_strchr(IS_TOKEN, *input) && *input != '-')
				check_cmd(&input, &tokens);
			else if (*input && *input == '-')
				check_options(&input, &tokens);
			else if (*input && check_tokens(&input, &tokens))
				continue ;
			else
				input++;
		}
	}
	add_index_token(tokens);
	return (tokens);
}
