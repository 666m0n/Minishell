/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:28:54 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/17 15:28:12 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	builtin_export(t_cmd *cmd, t_ctx *ctx)
{
	char	**args;
	int		i;
	int		status;

	if (!cmd || !cmd->args)
		return (ERROR);
	args = cmd->args;
	if (args[1] == NULL)
		return (display_sorted_env(ctx));
	status = SUCCESS;
	i = 1;
	while (args[i])
	{
		if (update_env_variable(ctx, args[i]) == ERROR)
			status = ERROR;
		i++;
	}
	return (status);
}

static int	add_new_var(t_ctx *ctx, const char *name, const char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (ERROR);
	new->id = ft_strdup(name);
	new->value = value ? ft_strdup(value) : NULL;
	if (!new->id || (value && !new->value))
	{
		free_env_var(new);
		return (ERROR);
	}
	new->raw = build_raw_string(name, value);
	if (!new->raw)
	{
		free_env_var(new);
		return (ERROR);
	}
	new->next = ctx->envp;
	ctx->envp = new;
	return (SUCCESS);
}

static int	update_env_variable(t_ctx *ctx, const char *arg)
{
	char	*name;
	char	*value;
	t_env	*existing;
	int		status;

	if (!is_valid_export_syntax(arg))
		return (handle_builtin_error("export", arg, "not a valid identifier"));
	if (extract_name_value(arg, &name, &value) == ERROR)
		return (ERROR);
	if (!is_valid_identifier(name))
	{
		cleanup_name_value(name, value);
		return (handle_builtin_error("export", arg, "not a valid identifier"));
	}
	existing = find_existing_var(ctx->envp, name);
	if (existing)
		status = update_existing_var(existing, name, value);
	else
		status = add_new_var(ctx, name, value);
	cleanup_name_value(name, value);
	return (status);
}
