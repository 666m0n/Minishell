/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42Paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:30:54 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/26 17:57:58 by sviallon         ###   ########.fr       */
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
	size_t	len;
	size_t	full_len;

	full_len = ft_strlen(s);
	to_ret = NULL;
	if (ft_isdigit(s[start]))
	{
		tofind = ft_substr(s, start + 1, *i - start - 1);
		to_ret = ft_strdup(tofind);
		return (free(tofind), to_ret);
	}
	else
	{
		len = 0;
		while ((start + len < full_len
				&& ft_isalnum(s[start + len])) || s[start + len] == '_')
			len++;
		tofind = ft_substr(s, start, len);
	}
	return (end_expand(tofind, to_ret, data));
}

/* static char	*expand_zero(char *s, int start, int *i)
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
} */

char	*replace_var(char *s, t_ctx *data, size_t *i)
{
	int		start;
	int		y;

	y = *i;
	start = *i + 1;
	y++;
	while (s[y])
	{
		if (!ft_isalnum(s[y]) && s[y] != '_' && s[y] != '?')
			break ;
		y++;
	}
	if (s[y] == '\0')
		y--;
	if (s[start] == '0')
		return (ft_strdup("minishell"));
	else if (s[start] == '?')
	{
		(*i)++;
		return (ft_itoa(data->exit_code));
	}
	else
		return (expand_case(data, s, start, &y));
}
