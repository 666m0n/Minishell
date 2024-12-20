/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:03:21 by emmmarti          #+#    #+#             */
/*   Updated: 2024/12/12 19:32:53 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Configure les redirections pour une commande dans un pipeline
** @param pipe_array: tableau des pipes
** @param cmd_position: position dans le pipeline
** @param nb_pipes: nombre total de pipes
** Note: configure stdin/stdout selon la position (début/milieu/fin)
*/
void	configure_pipe_fds(t_pipe *pipe_array, int cmd_pos, int nb_of_pipes)
{
	if (cmd_pos == 0)
	{
		if (dup2(pipe_array[cmd_pos][1], STDOUT_FILENO) == SYSCALL_ERROR)
			exit(handle_system_error("dup2"));
		close(pipe_array[cmd_pos][1]);
	}
	else if (cmd_pos == nb_of_pipes)
	{
		if (dup2(pipe_array[cmd_pos - 1][0], STDIN_FILENO) == SYSCALL_ERROR)
			exit(handle_system_error("dup2"));
		close(pipe_array[cmd_pos - 1][0]);
	}
	else
	{
		if (dup2(pipe_array[cmd_pos - 1][0], STDIN_FILENO) == SYSCALL_ERROR)
			exit(handle_system_error("dup2"));
		close(pipe_array[cmd_pos - 1][0]);
		if (dup2(pipe_array[cmd_pos][1], STDOUT_FILENO) == SYSCALL_ERROR)
			exit(handle_system_error("dup2"));
		close(pipe_array[cmd_pos][1]);
	}
}

/*
** Crée un tableau de pipes pour le pipeline
** @param cmd: première commande du pipeline
** @param nb_of_pipes: nombre de pipes nécessaires
** @return: tableau de pipes alloué ou NULL si erreur
** Note: gère le nettoyage en cas d'échec partiel
*/
t_pipe	*create_pipe_array(int nb_of_pipes)
{
	t_pipe	*pipe_array;
	int		i;

	pipe_array = malloc (sizeof (int [2]) * nb_of_pipes);
	if (!pipe_array)
		return (NULL);
	i = 0;
	while (i < nb_of_pipes)
	{
		if (pipe(pipe_array[i]) == SYSCALL_ERROR)
		{
			while (--i >= 0)
			{
				if (close(pipe_array[i][0]) == SYSCALL_ERROR)
					exit(handle_system_error("close"));
				if (close(pipe_array[i][1]) == SYSCALL_ERROR)
					exit(handle_system_error("close"));
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
