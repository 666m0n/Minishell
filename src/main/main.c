/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:37:35 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/23 15:24:02 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_return	handle_loop(t_ctx *ctx)
{
	char		*line;
	t_pars_node	*tokens;
	t_command	*cmd;

	line = NULL;
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (line[0] != '\0' && check_line(line) == 0)
		{
			add_history(line);
			tokens = lexer(line, ctx);
			if (tokens)
			{
				print_tokens(tokens);
				cmd = parser(tokens);
				if (cmd)
				{
					print_command(cmd);
					free_command(cmd);
				}
				free_token(tokens);
			}
		}
		free(line);
		line = NULL;
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
