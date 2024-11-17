/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:05:03 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/17 15:28:07 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
t_bool	is_valid_export_syntax(const char *arg)
{
	int	i;

	if (!arg || !*arg)
		return (FALSE);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (i == 0)
		return (FALSE);
	return (TRUE);
}

t_bool	is_valid_identifier(const char *name)
{
	int	i;

	if (!name || !*name)
		return (FALSE);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (FALSE);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	extract_name_value(const char *arg, char **name, char **value)
{
	char	*equals;

	*name = NULL;
	*value = NULL;
	equals = ft_strchr(arg, '=');
	if (equals)
	{
		*name = ft_strndup(arg, equals - arg);
		*value = ft_strdup(equals + 1);
		if (!*name || !*value)
		{
			cleanup_name_value(*name, *value);
			return (ERROR);
		}
	}
	else
	{
		*name = ft_strdup(arg);
		if (!*name)
			return (ERROR);
	}
	return (SUCCESS);
}

char	*build_raw_string(const char *name, const char *value)
{
	char	*raw;
	char	*temp;

	if (!value)
		return (ft_strdup(name));
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	raw = ft_strjoin(temp, value);
	free(temp);
	return (raw);
}

void	cleanup_name_value(char *name, char *value)
{
	if (name)
		free(name);
	if (value)
		free(value);
}
