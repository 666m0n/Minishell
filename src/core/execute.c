/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:30:19 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/12 19:01:41 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Exécute une séquence de commandes reliées par des pipes
** @param cmd: première commande de la séquence
** @param pipe_array: tableau des pipes
** @param nb_of_pipes: nombre de pipes
** @param ctx: contexte du shell
** @return: code de sortie du dernier processus
*/
int	run_pipeline(t_cmd *cmd, t_pipe *pipe_array, int nb_of_pipes)
{
	t_cmd	*current;
	pid_t	*pid_array;
	int		position;
	int		status;

	if (init_pipeline(nb_of_pipes, &pid_array) != SUCCESS)
		return (ERROR);
	current = cmd;
	position = 0;
	while (current)
	{
		pid_array[position] = \
		fork_pipeline_process(current, pipe_array, position, nb_of_pipes);
		if (pid_array[position] == SYSCALL_ERROR)
		{
			cleanup_remaining_pipes(pipe_array, nb_of_pipes);
			free(pid_array);
			return (handle_system_error("fork"));
		}
		current = current->next;
		position++;
	}
	status = wait_for_processes(pid_array, nb_of_pipes + 1);
	cleanup_remaining_pipes(pipe_array, nb_of_pipes);
	return (status);
}

/*
** Gère l'exécution d'un pipeline complet
** @param cmd: première commande du pipeline
** @param ctx: contexte du shell
** @return: code de sortie du pipeline ou erreur
** Note: crée les pipes, lance l'exécution et nettoie
*/
int	exec_pipe(t_cmd *cmd)
{
	int		status;
	int		nb_of_pipes;
	t_pipe	*pipe_array;

	nb_of_pipes = count_pipes(cmd);
	pipe_array = create_pipe_array(nb_of_pipes);
	if (!pipe_array)
		return (PIPE_ERROR);
	status = run_pipeline(cmd, pipe_array, nb_of_pipes);
	free(pipe_array);
	cleanup_fds(cmd);
	return (status);
}

/*
** Attend la fin d'un processus et traite son statut de sortie
** @param pid: identifiant du processus à attendre
** @return: code de sortie standard ou code d'erreur si échec
** Note: gère les interruptions et les signaux spéciaux (SIGQUIT)
*/
int	wait_process_status(pid_t pid)
{
	int	status;

	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno != EINTR)
			return (handle_system_error("waitpid"));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n\n", 19);
		return (128 + WTERMSIG(status));
	}
	return (ERROR);
}

/*
** Exécute une commande simple (sans pipe) en créant un processus fils
** @param cmd: commande à exécuter
** @param ctx: contexte du shell
** @return: code de sortie de la commande ou code d'erreur
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
	status = wait_process_status(pid);
	cleanup_fds(cmd);
	return (status);
}

/*
** Exécute une commande builtin
** @param cmd: commande builtin à exécuter
** @param ctx: contexte du shell
** @return: code de sortie du builtin
** Note: gère les redirections si présentes
*/
int	exec_builtin(t_cmd *cmd, t_ctx *ctx, t_bool skip_redirections)
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
	if (has_redirection(cmd) && skip_redirections == FALSE)
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
