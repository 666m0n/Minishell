/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:22:44 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/15 11:18:18 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Trouve le chemin complet d'une commande
** - Gère les chemins absolus/relatifs
** - Cherche dans PATH si nom simple
** @param cmd_name: nom ou chemin de la commande
** @return: chemin complet alloué ou NULL si non trouvé
** Note: le retour doit être libéré par l'appelant
*/
char	*find_command_path(const char *cmd_name)
{
	char	*path;
	char	**directories;
	char	*full_path;

	if (cmd_name == NULL)
		return (NULL);
	if (is_path(cmd_name)  == TRUE)
	{
		if (access(cmd_name, F_OK) == SYSCALL_SUCCESS)
			return (ft_strdup(cmd_name));
		return (NULL);
	}
	path = getenv("PATH");
	if (path == NULL)
		path = DEFAULT_PATH;
	directories = ft_split(path, ':');
	if (directories == NULL)
		return (NULL);
	full_path = search_in_directory(directories, cmd_name);
	ft_free_array(directories);
	return (full_path);
}
