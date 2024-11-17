/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:12:08 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/17 15:27:59 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	print_export_var(t_env *var)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(var->id, STDOUT_FILENO);
	if (var->value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(var->value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

static t_env	*find_next_in_sort(t_env *env, const char *last)
{
	t_env	*next;
	t_env	*current;

	next = NULL;
	current = env;
	while (current)
	{
		if ((!last || ft_strcmp(current->id, last) > 0) &&
			(!next || ft_strcmp(current->id, next->id) < 0))
			next = current;
		current = current->next;
	}
	return (next);
}

static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	display_sorted_env(t_ctx *ctx)
{
	t_env	*current;
	char	*last_printed;
	int		count;

	if (!ctx || !ctx->envp)
		return (SUCCESS);
	count = count_env_vars(ctx->envp);
	last_printed = NULL;
	while (count--)
	{
		current = find_next_in_sort(ctx->envp, last_printed);
		if (!current)
			break ;
		print_export_var(current);
		last_printed = current->id;
	}
	return (SUCCESS);
}
