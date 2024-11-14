/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:51:59 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/14 19:07:40 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

close_unused_pipes(t_pipe *pipe_array, int cmd_position, int nb_of_pipes)
{
	int i;

	i = 0;
	while (i < nb_of_pipes)
	{
		if (i != cmd_position - 1)
			close(pipe_array[i][0]);
		if (i != cmd_position)
			close(pipe_array[i][1]);
		i++;
	}
}

void	configure_pipe_fds(t_pipe *pipe_array, int cmd_position, int nb_of_pipes)
{
	if (cmd_position == 0)
	{
		dup2(pipe_array[cmd_position][1], STDOUT_FILENO);
	}
	else if (cmd_position == nb_of_pipes)
	{
		dup2(pipe_array[cmd_position - 1][0], STDIN_FILENO);
	}
	else
	{
		dup2(pipe_array[cmd_position  - 1][0], STDIN_FILENO);
		dup2(pipe_array[cmd_position][1], STDOUT_FILENO);
	}
}

/*
** Crée un tableau avec les pipes :
** C'est à dire une paire de descripteurs de fichiers (FDs) connectés,
** tout ce qui est écrit dans l'un peut être lu dans l'autre.
** renvoie un taleau : [nb_of_pipes][2]
*/
t_pipe *create_pipe_array(t_cmd *cmd, int nb_of_pipes)
{
	t_pipe	*pipe_array;
	int		i;

	pipe_array = malloc(sizeof(int[2]) * nb_of_pipes);
	if (!pipe_array)
		return (handle_system_error("malloc"));
	i = 0;
	while (i < nb_of_pipes)
	{
		if (pipe(pipe_array[i]) == SYSCALL_ERROR)
		{
			while (--i >= 0)
			{
				close(pipe_array[i][0]);
				close(pipe_array[i][1]);
			}
			free(pipe_array);
			return (NULL);
		}
		i++;
	}
	return (pipe_array);
}

int	count_pipes(t_cmd *cmd)
{
	int		nb_of_pipes;
	t_cmd	*current;

	nb_of_pipes = 0;
	current = cmd;
	while (current)
	{
		nb_of_pipes++;
		current = current->next;
	}
	return (nb_of_pipes - 1);
}
