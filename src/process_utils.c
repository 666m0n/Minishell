/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:00:00 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/06 12:05:39 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Crée un nouveau processus en utilisant fork()
** @return:
**  - SYSCALL_ERROR (-1) en cas d'erreur
**  - SYSCALL_SUCCESS (0) dans le processus enfant
**  - PID du processus enfant (> 0) dans le processus parent
** @details:
**  Fork() crée une copie exacte du processus appelant. Les deux processus
**  continueront l'exécution à partir du point de retour de fork().
**  Cette fonction est essentielle pour l'exécution de commandes externes
**  car elle permet d'isoler leur exécution dans un processus séparé.
*/
pid_t	create_child_process(void)
{
	return (fork());
}

/*
** Exécute une commande dans le processus enfant
** Cette fonction ne retourne jamais car elle termine soit par:
** - un exit() si une erreur survient
** - un execve() qui remplace le processus par la commande
** @param cmd: structure contenant la commande à exécuter
** @param ctx: contexte d'exécution
*/
void	exec_in_child(t_command *cmd, t_ctx *ctx)
{
	char	*cmd_path;
	char	**env;
	int		status;

	if (!cmd || !cmd->cmd || !ctx)
		exit(ERROR);
	if (setup_redirections(cmd->cmd->redirections) != SUCCESS)
		exit(ERROR);
	cmd_path = get_command_path(cmd);
	if (cmd_path == NULL)
		exit(CMD_NOT_FOUND);
	env = env_to_array(ctx->envp);
	if (!env)
	{
		free(cmd_path);
		exit(MEMORY_ERROR);
	}
	status = execve(cmd_path, cmd->cmd->args, env);
	free(cmd_path);
	ft_free_array(env);
	exit(status);
}

/*
** Attend la fin d'un processus enfant et retourne son code de sortie
** @param pid: PID du processus enfant à attendre
** @return:
**   - Le code de sortie du processus (0-255) en cas de succès
**   - ERROR en cas d'échec de waitpid
*/
int	wait_child(pid_t pid)
{
	int	status;
	int	high_bits;
	int	exit_code;

	if (waitpid(pid, &status, 0) == SYSCALL_ERROR)
		return (ERROR);
	high_bits = status & EXIT_CODE_MASK;
	exit_code = high_bits >> EXIT_CODE_SHIFT;
	return (exit_code);
}
