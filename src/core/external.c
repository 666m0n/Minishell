/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:09:40 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/12 14:10:43 by emmmarti         ###   ########.fr       */
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

static void	setup_child_env(t_cmd *cmd, t_ctx *ctx)
{
	char	**env_array;

	env_array = NULL;
	env_array = env_to_array(ctx->envp);
	if (!env_array)
	{
		cleanup_fds(cmd);
		exit(MEMORY_ERROR);
	}
	execve(cmd->path, cmd->args, env_array);
	ft_free_array(env_array);
	cleanup_fds(cmd);
	exit(handle_system_error("execve"));
}

void	exec_in_child(t_cmd *cmd, t_ctx *ctx)
{
	setup_child_signals();
	if (has_redirection(cmd))
	{
		if (setup_redirections(cmd) != SUCCESS)
		{
			cleanup_fds(cmd);
			exit(ERROR);
		}
	}
	setup_child_env(cmd, ctx);
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
