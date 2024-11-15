/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:51:59 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/15 11:28:12 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Attend la fin de tous les processus du pipeline
** @param pids: tableau des PIDs des processus
** @param count: nombre de processus
** @return: code de sortie du dernier processus ou ERROR
*/
int wait_for_processes(pid_t *pids, int count)
{
	int i;
	int status;
	int last_status;

	i = 0;
	while (i < count)
	{
		if (waitpid(pids[i], &status, 0) == SYSCALL_ERROR)
			return (handle_system_error("waitpid"));

		if (i == count - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (last_status);
}

/*
** Ferme les descripteurs de pipe inutilisés pour une position donnée
** @param pipe_array: tableau des pipes
** @param cmd_position: position de la commande dans le pipeline
** @param nb_of_pipes: nombre total de pipes
*/
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

/*
** Configure les redirections pour une commande dans un pipeline
** @param pipe_array: tableau des pipes
** @param cmd_position: position dans le pipeline
** @param nb_pipes: nombre total de pipes
** Note: configure stdin/stdout selon la position (début/milieu/fin)
*/
void	configure_pipe_fds(t_pipe *pipe_array, int cmd_position, int nb_of_pipes)
{
	if (cmd_position == 0)
	{
		dup2(pipe_array[cmd_position][1], STDOUT_FILENO);
			exit(handle_system_error("dup2"));
	}
	else if (cmd_position == nb_of_pipes)
	{
		dup2(pipe_array[cmd_position - 1][0], STDIN_FILENO);
			exit(handle_system_error("dup2"));
	}
	else
	{
		dup2(pipe_array[cmd_position  - 1][0], STDIN_FILENO);
			exit(handle_system_error("dup2"));
		dup2(pipe_array[cmd_position][1], STDOUT_FILENO);
			exit(handle_system_error("dup2"));
	}
}

/*
** Crée un tableau de pipes pour le pipeline
** @param cmd: première commande du pipeline
** @param nb_of_pipes: nombre de pipes nécessaires
** @return: tableau de pipes alloué ou NULL si erreur
** Note: gère le nettoyage en cas d'échec partiel
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

/*
** Compte le nombre de pipes nécessaires dans la chaîne de commandes
** @param cmd: première commande du pipeline
** @return: nombre de pipes (nb_commandes - 1)
*/
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
