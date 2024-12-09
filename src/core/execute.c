/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Simon <Simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:30:19 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/09 10:14:45 by Simon            ###   ########.fr       */
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
int	run_pipeline(t_cmd *cmd, t_pipe *pipe_array, int nb_of_pipes, t_ctx *ctx)
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
        pid_array[position] = fork_pipeline_process(current, pipe_array, position, nb_of_pipes, ctx);
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
int	exec_pipe(t_cmd *cmd, t_ctx *ctx)
{
	int		status;
	int		nb_of_pipes;
	t_pipe	*pipe_array;

	nb_of_pipes = count_pipes(cmd);
	pipe_array = create_pipe_array(nb_of_pipes);
	if (!pipe_array)
		return (PIPE_ERROR);
	status = run_pipeline(cmd, pipe_array, nb_of_pipes, ctx);
	free(pipe_array);
	cleanup_fds(cmd);
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
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_in_child(cmd, ctx);
	}
	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno != EINTR)
			return (handle_system_error("waitpid"));
	}
	cleanup_fds(cmd);
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

/*
** Point d'entrée principal pour l'exécution des commandes
** @param cmd: commande à exécuter
** @param ctx: contexte du shell
** @return: code de sortie de la commande
** Note: détecte le type (builtin/simple/pipe) et redirige
** divise en 2 pour la gestion des signaux
*/
int	execute_command(t_cmd *cmd, t_ctx *ctx)
{
	const char	*cmd_name;
	int			status;

	if (!cmd || !ctx)
		return (ERROR);
	cmd_name = get_cmd_name(cmd);
	if (!cmd_name)
		return (CMD_NOT_FOUND);
	status = process_heredocs(cmd);
	if (status != SUCCESS)
		return (status);
	return (execute_cmd_type(cmd, ctx, cmd_name));
}
