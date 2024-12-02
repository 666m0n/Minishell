/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:54:02 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/02 15:20:18 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_numeric_error(const char *arg)
{
	char	*tmp;

	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	tmp = ft_strdup(arg);
	if (tmp)
	{
		ft_putstr_fd(tmp, STDERR_FILENO);
		free(tmp);
	}
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit(2);
}

static int	handle_too_many_args(void)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	return (ERROR);
}

int	builtin_exit(t_cmd *cmd, t_ctx *ctx)
{
	int		status;
	char	*arg;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!cmd->args[1])
		exit(ctx->exit_code);
	arg = cmd->args[1];
	status = handle_numeric_arg(arg);
	if (status == INVALID_NUMERIC_ARG)
		write_numeric_error(arg);
	if (cmd->args[2])
		return (handle_too_many_args());
	exit(status);
}
