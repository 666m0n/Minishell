/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:51:59 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/12 19:03:18 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Attend la fin de tous les processus du pipeline
** @param pids: tableau des PIDs des processus
** @param count: nombre de processus
** @return: code de sortie du dernier processus ou ERROR
*/
int	wait_for_processes(pid_t *pids, int count)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = ERROR;
	while (i < count)
	{
		if (waitpid(pids[i], &status, 0) == SYSCALL_ERROR)
		{
			free(pids);
			return (handle_system_error("waitpid"));
		}
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	free(pids);
	return (last_status);
}

static void	close_first_cmd_pipes(t_pipe *pipe_array, int nb_of_pipes)
{
	int	i;

	i = 0;
	while (i < nb_of_pipes)
	{
		if (i == 0)
			close(pipe_array[i][0]);
		else
		{
			close(pipe_array[i][0]);
			close(pipe_array[i][1]);
		}
		i++;
	}
}

static void	close_last_cmd_pipes(t_pipe *pipe_array, int pos, int nb_of_pipes)
{
	int	i;

	i = 0;
	while (i < nb_of_pipes)
	{
		if (i == pos - 1)
			close(pipe_array[i][1]);
		else
		{
			close(pipe_array[i][0]);
			close(pipe_array[i][1]);
		}
		i++;
	}
}

static void	close_middle_cmd_pipes(t_pipe *pipe_array, int pos, int nb_of_pipes)
{
	int	i;

	i = 0;
	while (i < nb_of_pipes)
	{
		if (i == pos - 1)
			close(pipe_array[i][1]);
		else if (i == pos)
			close(pipe_array[i][0]);
		else
		{
			close(pipe_array[i][0]);
			close(pipe_array[i][1]);
		}
		i++;
	}
}

void	close_unused_pipes(t_pipe *pipe_array, int cmd_position, \
					int nb_of_pipes)
{
	if (cmd_position == 0)
		close_first_cmd_pipes(pipe_array, nb_of_pipes);
	else if (cmd_position == nb_of_pipes)
		close_last_cmd_pipes(pipe_array, cmd_position, nb_of_pipes);
	else
		close_middle_cmd_pipes(pipe_array, cmd_position, nb_of_pipes);
}
