/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:37:35 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/08 13:49:10 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_command(t_ctx *ctx, t_command *cmd)
{
	if (!cmd || !cmd->cmd || !cmd->cmd->args || !cmd->cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->cmd->args[0], "env") == 0)
		ctx->exit_code = bui_env(ctx, cmd->cmd);
	print_command(cmd);
	return (1);
}

static void	process_line(char *line, t_ctx *ctx)
{
	t_token		*tokens;
	t_command	*cmd;

	tokens = lexer(line, ctx->envp, ctx->exit_code);
	if (tokens)
	{
		print_tokens(tokens);
		cmd = parser(tokens);
		if (cmd)
		{
			execute_command(ctx, cmd);
			free_command(cmd);
		}
		free_token(tokens);
	}
}

t_return	handle_loop(t_ctx *ctx)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		if (line[0] != '\0' && !check_line(line))
		{
			add_history(line);
			process_line(line, ctx);
		}
		free(line);
	}
	return (SUCCESS);
}

void	free_all(t_ctx *ctx)
{
	if (!ctx)
		return ;
	if (ctx->envp)
		env_free(ctx->envp);
	rl_clear_history();
	free(ctx);
}

int	main(int ac, char **av, char **envp)
{
	t_ctx		*ctx;
	t_return	status;

	(void) av;
	(void) ac;
	ctx = init_ctx(envp);
	if (!ctx)
		return (EXIT_FAILURE);
	status = handle_loop(ctx);
	free_all(ctx);
	if (status == SUCCESS)
	{
		ft_putstr_fd("ciao !\n", 2);
		return (EXIT_SUCCESS);
	}
	ft_putstr_fd("c cassé\n", 2);
	return (EXIT_FAILURE);
}
