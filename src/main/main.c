/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:37:35 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/13 12:57:05 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_status = 0;

static void	process_line(char *line, t_ctx *ctx)
{
	t_lexer		*tokens;
	t_cmd		*cmd;

	tokens = lexer(line);
	ctx->current_token = tokens;
	if (tokens)
	{
		if (syntax_tokens(tokens, ctx) == SUCCESS)
		{
			cmd = parser(tokens, ctx);
			if (cmd)
			{
				ctx->cmd = cmd;
				execute_command(cmd, ctx);
				if (cmd->args && ft_strncmp(cmd->args[0], "exit", 5) != 0)
				{
					free_cmd(cmd);
					ctx->cmd = NULL;
				}
			}
		}
		free_token(tokens);
		ctx->current_token = NULL;
	}
}

t_return	handle_loop(t_ctx *ctx)
{
	char	*line;

	line = NULL;
	setup_interactive_signals();
	printf("\033[2J\033[H");
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			return (ctx->exit_code);
		}
		if (!check_line(line))
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

	if (*envp)
	{
		(void) av;
		(void) ac;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		ctx = init_ctx(envp);
		if (!ctx)
			return (EXIT_FAILURE);
		status = handle_loop(ctx);
		if (status != SUCCESS)
		{
			status = ctx->exit_code;
			free_all(ctx);
			exit(status);
		}
		free_all(ctx);
		return (0);
	}
	ft_putstr_fd("remet l'environnement avant de me lancer petit malin", 2);
	return (0);
}
