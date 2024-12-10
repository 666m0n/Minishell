/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:37:35 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/10 15:59:09 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_status = 0;

// debug fd
void debug_fds(const char *location, pid_t pid)
{
    printf("\n[DEBUG FDs] %s (PID: %d)\n", location, pid);
    for (int fd = 0; fd < 256; fd++) {
        if (fcntl(fd, F_GETFD) != -1) {
            printf("FD %d is open\n", fd);
        }
    }
    printf("--------------------\n");
}

void check_fds(void)
{
    int fd;

    fd = 0;
    while (fd < 10)
    {
        if (fcntl(fd, F_GETFL) != -1)
            ft_printf("FD %d is open\n", fd);
        fd++;
    }
}


static void	process_line(char *line, t_ctx *ctx)
{
	t_lexer		*tokens;
	t_cmd		*cmd;
    
	tokens = lexer(line);
    // fin
	if (tokens)
	{
    	/* print_tokens(tokens); */
        if (syntax_tokens(tokens, ctx) == SUCCESS)
		{
			cmd = parser(tokens, ctx);
			if (cmd)
			{
				/* print_command(cmd); */
    			execute_command(cmd, ctx);
				free_cmd(cmd);
			}
		}
		free_token(tokens);
	}
}

t_return	handle_loop(t_ctx *ctx)
{
	char	*line;

	line = NULL;
	printf("\033[2J\033[H");
	while (1)
	{
		setup_interactive_signals();
		g_sig_status = 0;
		line = readline(PROMPT);
		if (!line)
		{
            // JE PENSE QU'il FAUDRAIT APPELER FONCTION DE CLEAN DE LA MEMOIRE ICI
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
