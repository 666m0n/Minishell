/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:40:50 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/11 16:30:35 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ctx	*init_ctx(char **envp)
{
	t_ctx	*ctx;

	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
		return (NULL);
	ctx->envp = create_env_list(envp);
	if (!ctx->envp)
	{
		free(ctx);
		return (NULL);
	}
	ctx->def_in = STDIN_FILENO;
	ctx->def_out = STDOUT_FILENO;
	ctx->exit_code = 0;
	return (ctx);
}

void	free_all(t_ctx	*ctx)
{
	if (ctx)
	{
		if (ctx->envp)
			env_free(ctx->envp);
		free(ctx);
	}
	rl_clear_history();
}

int	check_line(char *line)
{
	if (line[0] == '\0')
		return (TRUE);
	return (FALSE);
}
