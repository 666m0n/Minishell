/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinstest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:46:49 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/18 17:46:27 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//execute le bon builtin
int	execute_builtin(t_ctx *ctx, t_cmd *cmd)
{
	if (!cmd->args || !cmd->args[0])
		return (EXIT_FAILURE);
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (bui_env(ctx, cmd));
	return (EXIT_SUCCESS);
}
