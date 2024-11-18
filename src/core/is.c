/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:19:01 by emmmarti          #+#    #+#             */
/*   Updated: 2024/11/18 18:04:02 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Vérifie si la commande est un chemin (absolu ou relatif)
** @param cmd_name: nom de la commande
** @return: TRUE si commence par '/' ou './' ou '../', FALSE sinon
*/
t_bool	is_path(const char *cmd_name)
{
	if (!cmd_name)
		return (FALSE);
	if (cmd_name[0] == '/')
		return (TRUE);
	if (cmd_name[0] == '.' && cmd_name[1] == '/')
		return (TRUE);
	if (cmd_name[0] == '.' && cmd_name[1] == '.' && cmd_name[2] == '/')
		return (TRUE);
	return (FALSE);
}

/*
** Vérifie si le chemin correspond à un dossier
** @param path: chemin à vérifier
** @return: TRUE si c'est un dossier accessible, FALSE sinon
*/
t_bool	is_dir(const char *path)
{
	DIR	*dir;

	if (!path || !*path)
		return (FALSE);
	dir = opendir(path);
	if (!dir)
		return (FALSE);
	closedir(dir);
	return (TRUE);
}

/*
** Vérifie si la commande est un builtin
** @param cmd_name: nom de la commande
** @return: TRUE si c'est un builtin (echo, cd, pwd...), FALSE sinon
*/
t_bool	is_builtin(const char *cmd_name)
{
	int					i;
	static const char	*builtins[] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(cmd_name, builtins[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/*
** Vérifie si c'est une commande simple (sans pipe)
** @param cmd: structure de commande
** @return: TRUE si pas de commande suivante dans le pipe, FALSE sinon
*/
t_bool	is_simple_command(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (FALSE);
	if (cmd->next == NULL)
		return (TRUE);
	else
		return (FALSE);
}

t_bool	is_valid_command(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (FALSE);
	return (TRUE);
}
