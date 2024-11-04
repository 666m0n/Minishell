/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:49:11 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/04 11:44:37 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** echo avec option -n
** Retourne 0 en cas de succès, 1 sinon
*/
int	builtin_echo(t_command *cmd, t_ctx *ctx)
{
	char	**args;
	int		i;
	t_bool	n_option;

	(void)ctx;
	if (!cmd || !cmd->cmd || !cmd->cmd->args)
		return (ERROR);
	args = cmd->cmd->args;
	if (args[1] == NULL)
	{
		ft_printf("\n");
		return (SUCCESS);
	}
	i = 1;
	n_option = FALSE;
	if (ft_strcmp(args[1], "-n") == 0)
	{
		n_option = TRUE;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!n_option)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS);
}

/*
** pwd sans options
** Retourne 0 en cas de succès, 1 sinon
*/
int	builtin_pwd(t_command *cmd, t_ctx *ctx)
{
	char	*current_path;

	(void)cmd;
	(void)ctx;
	current_path = getcwd(NULL, 0);
	if (!current_path)
		return (handle_system_error("pwd"));
	ft_putstr_fd(current_path, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	free(current_path);
	return (SUCCESS);
}

/*
** env sans options ni arguments
** Retourne 0 en cas de succès, 1 sinon
*/
int	builtin_env(t_command *cmd, t_ctx *ctx)
{
	t_env	*current;

	if (cmd->cmd->args[1])
		return (handle_builtin_error("env", cmd->cmd->args[1],
			"too many arguments"));
	current = ctx->envp;
	while (current)
	{
		if (current->value)
		{
			ft_putstr_fd(current->id, STDOUT_FILENO);
			write(STDOUT_FILENO, "=", 1);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
		}
		current = current->next;
	}
	return (SUCCESS);
}

/*
** exit sans options
** Note: Gestion spéciale car termine le shell
*/
int	builtin_exit(t_command *cmd, t_ctx *ctx)
{
	int	exit_code;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!cmd->cmd->args[1])
	{
		exit_code = ctx->exit_code;
		free_all(ctx);
		exit(exit_code);
	}
	if (!ft_str_isdigit(cmd->cmd->args[1]))
	{
		handle_builtin_error("exit", cmd->cmd->args[1],
			"numeric argument required");
		free_all(ctx);
		exit(2);
	}
	exit_code = ft_atoi(cmd->cmd->args[1]);
	if (cmd->cmd->args[2])
		return (handle_builtin_error("exit", NULL, "too many arguments"));
	free_all(ctx);
	exit(exit_code % 256);
}
