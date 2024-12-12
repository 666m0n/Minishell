/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:19:09 by Simon             #+#    #+#             */
/*   Updated: 2024/12/12 18:52:18 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_handler(int signum)
{
	write(2, "quit (core dumped)\n", 19);
	(void)signum;
}

void	heredoc_signal_handler(int signum)
{
	struct termios	term;

	rl_on_new_line();
	rl_replace_line("", 0);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	exit(1);
	(void)signum;
}
