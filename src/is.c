/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:19:01 by emmmarti          #+#    #+#             */
/*   Updated: 2024/11/11 16:23:15 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	is_builtin(const char *cmd_name)
{
	int					i;
	static const char	*builtins[] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(cmd_name, builtins[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}
