/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:19:09 by Simon             #+#    #+#             */
/*   Updated: 2024/12/11 13:06:16 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_handler(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "Quit (core dumped)\n", 18);
}
