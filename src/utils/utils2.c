/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:33:28 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/22 22:15:18 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strcat(char *dest, char *src)
{
	size_t	i;
	size_t	lengthdest;

	if (!dest || !src)
		return (0);
	lengthdest = 0;
	i = 0;
	while (dest[lengthdest])
		lengthdest++;
	while (src[i])
	{
		dest[lengthdest + i] = src[i];
		i++;
	}
	dest[lengthdest + i] = '\0';
	return (lengthdest + i);
}

size_t	ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	if (!dest || !src)
		return (0);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}

void	skip_consecutive_quotes(char **str, char *quote_type, int *effective_q)
{
	int		count;
	char	*ptr;

	ptr = *str;
	count = 0;
	while (*ptr == *quote_type)
	{
		count++;
		ptr++;
	}
	*effective_q = (count % 2);
	if (count % 2 == 0)
	{
		*str = ptr;
		if (**str == '\'' || **str == '"')
			*quote_type = **str;
	}
	else
		*str += count - 1;
}

t_token	get_quote_type(char quote)
{
	if (quote == '"')
		return (T_DQUOTE);
	return (T_SQUOTE);
}

char	*get_quote_content(char **str, char quote)
{
	char	*start;
	char	*content;

	if (!str || !*str)
		return (NULL);
	start = *str;
	while (**str && **str != quote)
	{
		if (!*str)
			return (NULL);
		(*str)++;
	}
	if (!*str)
		return (NULL);
	content = ft_substr(start, 0, *str - start);
	return (content);
}
