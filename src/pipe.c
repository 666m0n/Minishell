/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:51:59 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/14 12:03:14 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Crée un tableau avec les pipes :
** C'est à dire une paire de descripteurs de fichiers (FDs) connectés,
** tout ce qui est écrit dans l'un peut être lu dans l'autre.
** renvoie un taleau : [nb_of_pipes][2]
*/
t_pipe *create_pipe_array(t_cmd *cmd, int nb_of_pipes)
{
	int		(*pipe_array)[2];
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
