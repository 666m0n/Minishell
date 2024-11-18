/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:28:54 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/18 15:03:35 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* builtin_export.c */
int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	i++;
	}
	return (1);
}

static void	print_export_var(t_env *var)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(var->id, STDOUT_FILENO);
	if (var->value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(var->value, STDOUT_FILENO);
		ft_putchar_fd('\"', STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static t_env	*find_next_var(t_env *env, char *last)
{
	t_env	*next;
	t_env	*current;

	next = NULL;
	current = env;
	while (current)
	{
		if ((!last || ft_strcmp(current->id, last) > 0)
			&& (!next || ft_strcmp(current->id, next->id) < 0))
			next = current;
	current = current->next;
	}
	return (next);
}

static int	display_sorted_env(t_ctx *ctx)
{
	t_env	*current;
	char	*last;
	int		i;
	int		count;

	count = 0;
	current = ctx->envp;
	while (current && ++count)
	current = current->next;
	last = NULL;
	i = 0;
	while (i < count)
	{
		current = find_next_var(ctx->envp, last);
		if (current)
			print_export_var(current);
		last = current->id;
		i++;
	}
	return (SUCCESS);
}

int	builtin_export(t_cmd *cmd, t_ctx *ctx)
{
	int		i;
	t_env	*env;

	if (!cmd->args[1])
		return (display_sorted_env(ctx));
	i = 0;
	while (cmd->args[++i])
	{
		if (!is_valid_identifier(cmd->args[i]))
			return (handle_builtin_error("export", cmd->args[i],
					"not a valid identifier"));
		env = update_env_variable(ctx, cmd->args[i]);
		if (!env)
			return (ERROR);
	}
	return (SUCCESS);
}
