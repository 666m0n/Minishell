/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:28:37 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/29 18:21:05 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"


#include "minishell.h"

/*
** Vérifie si le chemin est relatif spécial (., .., ./ ou ../)
** @param path: chemin à vérifier
** @return: TRUE si chemin spécial, FALSE sinon
*/
static t_bool	is_special_path(const char *path)
{
	if (!path || !*path)
		return (FALSE);
	printf("Testing path: %s\n", path);
	if (ft_strcmp(path, ".") == 0 || ft_strcmp(path, "..") == 0)
	{
		printf("Is dot/dotdot path\n");
		return (TRUE);
	}
	if (ft_strncmp(path, "./", 2) == 0 || ft_strncmp(path, "../", 3) == 0)
	{
		printf("Is ./ or ../ path\n");
		return (TRUE);
	}
	printf("Not a special path\n");
	return (FALSE);
}

static int	change_directory(const char *path)
{
	printf("\nIn change_directory with path: %s\n", path);
	if (!path)
		return (ERROR);

	printf("Checking access F_OK: %d\n", access(path, F_OK));
	if (access(path, F_OK) == SYSCALL_ERROR)
		return (handle_builtin_error("cd", path, "No such file or directory"));

	printf("Checking is_dir: %d\n", is_dir(path));
	printf("Checking is_special_path: %d\n", is_special_path(path));
	if (!is_dir(path) && !is_special_path(path))
		return (handle_builtin_error("cd", path, "Not a directory"));

	printf("Checking access R_OK: %d\n", access(path, R_OK));
	if (access(path, R_OK) == SYSCALL_ERROR)
		return (handle_builtin_error("cd", path, "Permission denied"));

	printf("Attempting chdir\n");
	if (chdir(path) == SYSCALL_ERROR)
		return (handle_builtin_error("cd", NULL, strerror(errno)));

	printf("chdir successful\n");
	return (SUCCESS);
}

/*
** Implémente la commande cd 
** Gère les chemins relatifs et absolus
** @param cmd: structure commande
** @param ctx: contexte shell
** @return: SUCCESS si ok, code d'erreur sinon
*/
int	builtin_cd(t_cmd *cmd, t_ctx *ctx)
{
	char	**args;
    printf("DEBUG : On rentre dans builtin cd\n");
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

