/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:37:35 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/11 13:38:49 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_loop(/*variable d'env a init avant*/)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void) av;
	(void) ac;
	handle_loop();
}
