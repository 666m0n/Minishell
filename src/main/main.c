/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:37:35 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/25 17:28:27 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_status = 0;

static void	process_line(char *line, t_ctx *ctx)
{
	t_lexer		*tokens;
	t_cmd		*cmd;

	tokens = lexer(line);
	if (tokens)
	{
/*		print_tokens(tokens);*/
		cmd = parser(tokens, ctx);
		if (cmd)
		{
			/* print_command(cmd); */
			execute_command(cmd, ctx);
			free_cmd(cmd);
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
			return (-1);
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
