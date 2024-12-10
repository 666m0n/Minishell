/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:09:40 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/10 17:06:11 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Convertit la liste chaînée d'environnement en tableau pour execve
** @param env: liste chaînée des variables d'environnement
** @return: tableau de chaînes au format "nom=valeur", NULL si erreur
*/
static char	**env_to_array(t_env *env)
{
	t_env	*current;
	char	**array;
	int		size;

	size = 0;
	current = env;
	while (current && ++size)
		current = current->next;
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	current = env;
	size = 0;
	while (current)
	{
		array[size++] = current->raw;
		current = current->next;
	}
	array[size] = NULL;
	return (array);
}

/*
** Exécute une commande dans le processus fils
** - Configure les redirections si présentes
** - Exécute la commande via execve
** @param cmd: commande à exécuter
** @param ctx: contexte du shell
** Note: ne retourne jamais, termine le processus en cas d'erreur
*/
void	exec_in_child(t_cmd *cmd, t_ctx *ctx)
{
	char	**env_array;
	int		status;

    /* debug_fds("Start of exec_in_child before setup signal", getpid()); */
    setup_child_signals();
    /* debug_fds("Start of exec_in_child after setup signal", getpid()); */
	env_array = NULL;
 
	if (has_redirection(cmd))
	{
        /* debug_fds("Before setup redirections in child", getpid()); */
		status = setup_redirections(cmd);
        /* debug_fds("After setup redirections in child", getpid()); */
		if (status != SUCCESS)
		{
			cleanup_fds(cmd);
			exit(status);
		}
	}
    // debut ajout test debug fd
    if (cmd->fd->stdin_backup > 2)
        close(cmd->fd->stdin_backup);
    if (cmd->fd->stdout_backup > 2)
        close(cmd->fd->stdout_backup);
    //fin 
	env_array = env_to_array(ctx->envp);
	if (!env_array)
	{
		cleanup_fds(cmd);
		exit(MEMORY_ERROR);
	}
    /* debug_fds("  exec_in_child Just before execve", getpid()); */
	execve(cmd->path, cmd->args, env_array);
	ft_free_array(env_array);
	cleanup_fds(cmd);
	exit(handle_system_error("execve"));
}

/*
** Prépare l'exécution d'une commande externe
** - Vérifie l'existence de la commande
** - Vérifie les permissions
** - Trouve le chemin complet
** @param cmd: commande à préparer
** @return: SUCCESS ou code d'erreur approprié
*/
int	prepare_exec(t_cmd *cmd)
{
	const char	*cmd_name;
	char		*path;

	cmd_name = get_cmd_name(cmd);
	if (!cmd_name || !*cmd_name)
		return (CMD_NOT_FOUND);
/* 	if (is_dir(cmd_name) == TRUE)
		return (IS_DIR); */
	path = find_command_path(cmd_name, cmd->ctx);
	if (path == NULL)
		return (CMD_NOT_FOUND);
	if (access(path, X_OK) == SYSCALL_ERROR)
	{
		free(path);
		return (PERMISSION_DENIED);
	}
	if (set_cmd_path(cmd, path) != SUCCESS)
	{
		free(path);
		return (ERROR);
	}
	free(path);
	return (SUCCESS);
}
