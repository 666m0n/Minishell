/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:08:23 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/17 15:16:51 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Initialise le tableau des PIDs pour le pipeline
** @param nb_of_pipes: nombre de pipes dans le pipeline
** @return: tableau de PIDs alloué ou NULL si erreur
*/
static pid_t	*init_pipeline_processes(int nb_of_pipes)
{
	pid_t	*pid_array;

	pid_array = malloc(sizeof(pid_t) * (nb_of_pipes + 1));
	if (!pid_array)
		return (NULL);
	return (pid_array);
}

/*
** Execute une commande dans le processus fils du pipeline
** @param cmd: commande à exécuter
** @param pipe_array: tableau des pipes
** @param position: position dans le pipeline
** @param nb_of_pipes: nombre de pipes
** @param ctx: contexte du shell
** Note: ne retourne jamais, termine le processus
*/
static void	execute_pipeline_command(t_cmd *cmd, t_pipe *pipe_array, \
									int position, int nb_of_pipes, t_ctx *ctx)
{
	int	status;

	configure_pipe_fds(pipe_array, position, nb_of_pipes);
	close_unused_pipes(pipe_array, position, nb_of_pipes);
	if (is_builtin(cmd->args[0]))
		status = exec_builtin(cmd, ctx);
	else
	{
		status = prepare_exec(cmd);
		if (status != SUCCESS)
			exit(handle_command_error(cmd, status));
		exec_in_child(cmd, ctx);
	}
	exit(status);
}

/*
** Gère les pipes du processus parent pour une position donnée
** @param pipe_array: tableau des pipes
** @param position: position actuelle dans le pipeline
** @return: SUCCESS ou ERROR si problème de fermeture
*/
static int	handle_parent_pipes(t_pipe *pipe_array, int position)
{
	if (position > 0)
	{
		if (close(pipe_array[position - 1][0]) == SYSCALL_ERROR)
			return (ERROR);
		if (close(pipe_array[position - 1][1]) == SYSCALL_ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

/*
** Crée un nouveau processus pour une commande du pipeline
** @param cmd: commande à exécuter
** @param pipe_array: tableau des pipes
** @param position: position dans le pipeline
** @param nb_of_pipes: nombre de pipes
** @param ctx: contexte du shell
** @return: PID du processus créé ou -1 si erreur
*/
static pid_t    fork_pipeline_process(t_cmd *cmd, t_pipe *pipe_array, \
									int position, int nb_of_pipes, t_ctx *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid == SYSCALL_ERROR)
		return (SYSCALL_ERROR);
	if (pid == 0)
		execute_pipeline_command(cmd, pipe_array, position, nb_of_pipes, ctx);
	else if (handle_parent_pipes(pipe_array, position) == ERROR)
	{
		cleanup_remaining_pipes(pipe_array, nb_of_pipes);
		return (SYSCALL_ERROR);
	}
	return (pid);
}

/*
** Initialise le pipeline et vérifie les erreurs
** @param nb_of_pipes: nombre de pipes
** @param pid_array_ptr: pointeur vers le tableau de PIDs à initialiser
** @return: SUCCESS ou ERROR si échec d'allocation
*/
static int	init_pipeline(int nb_of_pipes, pid_t **pid_array_ptr)
{
	*pid_array_ptr = malloc(sizeof(pid_t) * (nb_of_pipes + 1));
	if (!*pid_array_ptr)
		return (handle_system_error("malloc"));
	return (SUCCESS);
}

