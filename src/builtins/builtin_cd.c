/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:28:37 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/03 19:01:01 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Obtient le chemin du répertoire personnel de l'utilisateur
** @param ctx: contexte contenant l'environnement
** @return: chemin du répertoire personnel ou NULL en cas d'erreur
*/
static char *get_home_directory(t_ctx *ctx)
{
	char	*home_path;

	home_path = getenv("HOME");
	if (home_path == NULL)
		return (NULL);
	return (home_path);
}

/*
** Gère le cas où cd est appelé sans argument
** Change le répertoire courant vers le répertoire personnel
** @param ctx: contexte contenant l'environnement
** @return: SUCCESS en cas de succès, ERROR sinon
*/
static int handle_no_args(t_ctx *ctx)
{
	char	*home_path;

	home_path = get_home_directory(ctx);
	if (home_path == NULL)
		return (handle_builtin_error("cd", NULL, "HOME not set"));
	if (chdir(home_path) == SYSCALL_ERROR)
		return (handle_builtin_error("cd", NULL, strerror(errno)));
	return (SUCCESS);
}

/*
** Gère le changement de répertoire avec un chemin spécifique
** @param path: chemin vers lequel changer
** @return: SUCCESS en cas de succès, ERROR sinon
*/
static int change_directory(const char *path)
{
	if (chdir(path) == SYSCALL_ERROR)
	{
		if (access(path, F_OK) == SYSCALL_ERROR)
			return (handle_builtin_error("cd", path, "No such file or directory"));
		else if (access(path, R_OK) == SYSCALL_ERROR)
			return (handle_builtin_error("cd", path, "Permission denied"));
		else if (is_dir(path) == FALSE)
			return (handle_builtin_error("cd", path, "Not a directory"));
		else
			return (handle_builtin_error("cd", NULL, strerror(errno)));
	}
	return (SUCCESS);
}

/*
** Implémente la commande builtin cd de bash
** @param cmd: structure contenant la commande et ses arguments
** @param ctx: contexte d'exécution
** @return: SUCCESS en cas de succès, ERROR en cas d'erreur
** Change le répertoire courant vers:
** - Le répertoire personnel si aucun argument n'est fourni
** - Le chemin spécifié en argument sinon
*/
int builtin_cd(t_command *cmd, t_ctx *ctx)
{
	char	**args;
	char	*target_path;
	int		status;

	if (cmd == NULL || cmd->cmd == NULL || cmd->cmd->args == NULL)
		return (ERROR);
	args = cmd->cmd->args;
	if (args[1] == NULL)
		return (handle_no_args(ctx));
	if (args[2] != NULL)
		return (handle_builtin_error("cd", NULL, "too many arguments"));
	target_path = args[1];
	status = change_directory(target_path);
	return (status);
}
