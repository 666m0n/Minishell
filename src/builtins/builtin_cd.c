/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:28:37 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/17 15:27:37 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Change le répertoire courant vers le chemin spécifié
** Gère les différents cas d'erreur :
**  chemin inexistant, permissions, pas un dossier
** @param path: chemin cible
** @return: SUCCESS si le changement a réussi,
**          ERROR sinon avec message d'erreur approprié
*/
static int	change_directory(const char *path)
{
	if (is_dir(path) == FALSE)
		return (handle_builtin_error("cd", path, "Not a directory"));
	if (access(path, F_OK) == SYSCALL_ERROR)
		return (handle_builtin_error("cd", path, "No such file or directory"));
	if (access(path, R_OK) == SYSCALL_ERROR)
		return (handle_builtin_error("cd", path, "Permission denied"));
	if (chdir(path) == SYSCALL_ERROR)
		return (handle_builtin_error("cd", NULL, strerror(errno)));
	return (SUCCESS);
}

/*
** Implémente la commande cd
** Change le répertoire courant selon les règles suivantes :
** - Requiert exactement un argument (chemin relatif ou absolu)
** - Vérifie l'existence et les permissions du chemin
** @param cmd: structure contenant la commande et ses arguments
** @param ctx: contexte du shell (non utilisé)
** @return: SUCCESS en cas de succès, ERROR en cas d'erreur
*/
int	builtin_cd(t_cmd *cmd, t_ctx *ctx)
{
	char	**args;

	(void)ctx;
	if (!cmd || !cmd->args)
		return (ERROR);
	args = cmd->args;
	if (args[1] == NULL)
		return (handle_builtin_error("cd", NULL, "path argument required"));
	if (args[2] != NULL)
		return (handle_builtin_error("cd", NULL, "too many arguments"));
	return (change_directory(args[1]));
}
