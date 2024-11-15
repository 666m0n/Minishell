/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:28:37 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/15 11:00:50 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Récupère le chemin du répertoire personnel ($HOME) depuis les variables
** d'environnement.
** @return: NULL si HOME n'est pas défini, sinon le chemin du répertoire
** personnel
*/
static char *get_home_directory(void)
{
	char	*home_path;

	home_path = getenv("HOME");
	if (home_path == NULL)
		return (NULL);
	return (home_path);
}

/*
** Change le répertoire courant vers $HOME quand cd est appelé sans argument
** @param ctx: contexte du shell
** @return: SUCCESS si le changement a réussi, ERROR sinon avec affichage de
** l'erreur appropriée
*/
static int handle_no_args(t_ctx *ctx)
{
	char	*home_path;

	(void)ctx;
	home_path = get_home_directory();
	if (home_path == NULL)
		return (handle_builtin_error("cd", NULL, "HOME not set"));
	if (chdir(home_path) == SYSCALL_ERROR)
		return (handle_builtin_error("cd", NULL, strerror(errno)));
	return (SUCCESS);
}

/*
** Change le répertoire courant vers le chemin spécifié
** Gère les différents cas d'erreur :
**  chemin inexistant, permissions, pas un dossier
** @param path: chemin cible
** @return: SUCCESS si le changement a réussi,
**			ERROR sinon avec message d'erreur approprié
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
** Implémente la commande cd
** Change le répertoire courant selon les règles suivantes :
** - Sans argument : change vers $HOME
** - Avec un argument : change vers le chemin spécifié
** - Avec plus d'un argument : erreur
** @param cmd: structure contenant la commande et ses arguments
** @param ctx: contexte du shell
** @return: SUCCESS en cas de succès, ERROR en cas d'erreur
*/
int builtin_cd(t_cmd *cmd, t_ctx *ctx)
{
	char	**args;
	char	*target_path;
	int		status;

	if (!cmd || !cmd->args)
		return (ERROR);
	args = cmd->args;
	if (args[1] == NULL)
		return (handle_no_args(ctx));
	if (args[2] != NULL)
		return (handle_builtin_error("cd", NULL, "too many arguments"));
	target_path = args[1];
	status = change_directory(target_path);
	return (status);
}
