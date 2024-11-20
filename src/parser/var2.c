/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:30:54 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/20 10:53:45 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*end_expand(char *tofind, char *to_ret, t_ctx *data)
{
	char	*var;

	var = NULL;
	var = get_env_value(data->envp, tofind);
	if (!var)
	{
		to_ret = ft_strdup("");
		if (!to_ret)
			return (NULL);
	}
	else
	{
		to_ret = ft_strdup(var);
		if (!to_ret)
			return (NULL);
	}
	if (tofind)
		free(tofind);
	return (to_ret);
}

static char	*expand_case(t_ctx *data, char *s, int start, int *i)
{
	char	*tofind;
	char	*to_ret;

	to_ret = NULL;
	if (s[(*i)++] == '?')
		return (ft_itoa(data->exit_code));
	else if (ft_isdigit(s[start]))
	{
		tofind = ft_substr(s, start + 1, *i - start - 1);
		if (!tofind)
			return (NULL);
		to_ret = ft_strdup(tofind);
		return (free(tofind), to_ret);
	}
	else
		tofind = ft_substr(s, start, *i - start);
	if (!tofind)
		return (NULL);
	return (end_expand(tofind, to_ret, data));
}

static char	*expand_zero(char *s, int start, int *i)
{
	char	*ifzero;
	char	*to_ret;

	if (s[start] == '0' && s[start + 1] == '\0')
		return ((*i)++, ft_strdup("minishell"));
	ifzero = ft_substr(s, start + 1, *i - start - 1);
	if (!ifzero)
		return (NULL);
	to_ret = ft_strdup("minishell");
	to_ret = ft_strjoin(to_ret, ifzero);
	return (free(ifzero), to_ret);
}

char	*replace_var(char *s, t_ctx *data, int *i)
{
	int	start;

	start = *i + 1;
	(*i)++;
	while (s[*i] && (s[*i] == '_' || ft_isalnum(s[*i]) || s[*i] == '?'))
	{
		if (s[*i] == '$' || s[*i] == '?')
			break ;
		(*i)++;
	}
	if (s[*i] == '\0')
		(*i)--;
	if (s[start] == '0')
		return (expand_zero(s, start, i));
	else
		return (expand_case(data, s, start, i));
}
