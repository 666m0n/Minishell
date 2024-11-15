/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:30:19 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/15 11:31:06 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Exécute une séquence de commandes reliées par des pipes
** @param cmd: première commande de la séquence
** @param pipe_array: tableau des pipes
** @param nb_of_pipes: nombre de pipes
** @param ctx: contexte du shell
** @return: code de sortie du dernier processus
*/
int	run_pipeline(t_cmd *cmd, t_pipe *pipe_array, int nb_of_pipes, t_ctx *ctx)
{
	t_cmd	*current;
	int		i;
	pid_t	pid;
	pid_t	*pid_array;
	int		status;

	current = cmd;
	i = 0;
	pid_array = malloc(sizeof(pid_t) * (nb_of_pipes + 1));
	if (!pid)
		return (handle_system_error("malloc"));
	while (current)
	{
		pid = fork();
		if (pid == SYSCALL_ERROR)
			return (handle_system_error("fork"));
		if (pid == 0)
		{
			configure_pipe_fds(pipe_array, i, nb_of_pipes);
			close_unused_pipes(pipe_array, i, nb_of_pipes);
			if (is_builtin(current) == TRUE)
				status = exec_builtin(current, ctx);
			else
			{
				status = prepare_exec(cmd);
				if (status != SUCCESS)
					return (handle_command_error(cmd, status));
				exec_in_child(cmd, ctx);
			}
			exit(status);
		}
		else
		{
			pid_array[i] = pid;
			if (i > 0)
			{
				close(pipe_array[i-1][0]);
				close(pipe_array[i-1][1]);
			}
		}
		current = current->next;
		i++;
	}
	status = wait_for_processes(pid_array, nb_of_pipes + 1);
    cleanup_remaining_pipes(pipe_array, nb_of_pipes);
	return (status)
}

/*
** Gère l'exécution d'un pipeline complet
** @param cmd: première commande du pipeline
** @param ctx: contexte du shell
** @return: code de sortie du pipeline ou erreur
** Note: crée les pipes, lance l'exécution et nettoie
*/
int	exec_pipe(t_cmd *cmd, t_ctx *ctx)
{
	int		status;
	int		nb_of_pipes;
	t_pipe	*pipe_array;

	nb_of_pipes = count_pipes(cmd);
	pipe_array = create_pipe_array(cmd, nb_of_pipes);
	if (!pipe_array)
		return (PIPE_ERROR);
	status = run_pipeline(cmd, pipe_array, nb_of_pipes, ctx);
	free(pipe_array);
	return (status);
}

/*
** Exécute une commande simple (sans pipe)
** @param cmd: commande à exécuter
** @param ctx: contexte du shell
** @return: code de sortie de la commande ou erreur
** Note: fork et attend la fin du processus fils
**
** TO DO :
** Géstion des signaux et nettoyage dans le cas d'interruption (ctrl C, ...)
*/
int	exec_simple(t_cmd *cmd, t_ctx *ctx)
{
	pid_t	pid;
	int		status;

	status = prepare_exec(cmd);
	if (status != SUCCESS)
		return (handle_command_error(cmd, status));
	pid = fork();
	if (pid == SYSCALL_ERROR)
		return (handle_system_error("fork"));
	if (pid == 0)
		exec_in_child(cmd, ctx);
	if (waitpid(pid, &status, 0) == SYSCALL_ERROR)
		return (handle_system_error("waitpid"));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (ERROR);
}

/*
** Exécute une commande builtin
** @param cmd: commande builtin à exécuter
** @param ctx: contexte du shell
** @return: code de sortie du builtin
** Note: gère les redirections si présentes
*/
int	exec_builtin(t_cmd *cmd, t_ctx *ctx)
{
	builtin_func	builtin;
	const char		*cmd_name;
	int				status;

	cmd_name = get_cmd_name(cmd);
	if (!cmd_name)
		return (ERROR);
	builtin = get_builtin_function(cmd_name);
	if (!builtin)
		return (ERROR);
	if (has_redirection(cmd))
	{
		status = setup_redirections(cmd);
		if (status != SUCCESS)
			return (status);
		status = builtin(cmd, ctx);
		if (restore_fds(cmd) != SUCCESS)
			status = ERROR;
		return (status);
	}
	return (builtin(cmd, ctx));
}

/*
** Point d'entrée principal pour l'exécution des commandes
** @param cmd: commande à exécuter
** @param ctx: contexte du shell
** @return: code de sortie de la commande
** Note: détecte le type (builtin/simple/pipe) et redirige
*/
int	execute_command(t_cmd *cmd, t_ctx *ctx)
{
	const char	*cmd_name;
	int			status;

	if (!cmd || !ctx)
		return (ERROR);
	// TO DO
	// Phase de prétraitement des heredocs
    // status = preprocess_heredocs(cmd);
    // if (status != SUCCESS)
    //   return (status);
	cmd_name = get_cmd_name(cmd);
	if (!cmd_name)
		return (CMD_NOT_FOUND);
	if (is_builtin(cmd_name) == TRUE)
		status = exec_builtin(cmd, ctx);
	else if (is_simple_command(cmd) == TRUE)
		status = exec_simple(cmd, ctx);
	else
		status = exec_pipe(cmd, ctx);
	set_exit_status(cmd, status);
	return (status);
}
