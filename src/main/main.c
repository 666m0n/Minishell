/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:37:35 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/14 15:39:16 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_return	handle_loop(t_ctx *ctx)
{
	char	*line;
	t_ctx	*ballec;

	ballec = ctx;
	line = NULL;
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		else if (check_line(line) == 0)
		{
			add_history(line);
			line = NULL;
		}
		if (line)
			free(line);
	}
	return (SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	t_ctx	*ctx;

	(void) av;
	(void) ac;
	ctx = init_ctx(envp);
	if (!ctx)
		return (EXIT_FAILURE);
	handle_loop(ctx);
	free_all(ctx);
	ft_putstr_fd("ciao !\n", 2);
	return (EXIT_FAILURE);
}
