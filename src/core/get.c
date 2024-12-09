/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:26:38 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/09 17:53:19 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Récupère le nom de la commande (premier argument)
** @param cmd: structure de commande
** @return: NULL si cmd invalide, sinon args[0]
*/
const char	*get_cmd_name(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (NULL);
	return (cmd->args[0]);
}

/*
** Récupère la liste des redirections de la commande
** @param cmd: structure de commande
** @return: NULL si pas de redirection, sinon pointeur vers la première
*/
t_redirection	*get_redirections(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	return (cmd->redirections);
}

/*
** Récupère le code de sortie de la dernière commande
** @param cmd: structure de commande
** @return: ERROR si cmd invalide, sinon le code de sortie
*/
int	get_exit_status(t_cmd *cmd)
{
	if (!cmd)
		return (ERROR);
	return (cmd->exit_status);
}

/*
** Récupère le chemin complet de la commande
** @param cmd: structure de commande
** @return: NULL si cmd invalide, sinon le chemin
*/
char	*get_cmd_path(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	return (cmd->path);
}

/*
** Retourne le pointeur de fonction du builtin correspondant
** @param cmd_name: nom de la commande
** @return: NULL si pas un builtin, sinon pointeur vers la fonction
*/
builtin_func	get_builtin_function(const char *cmd_name)
{
	if (!ft_strcmp(cmd_name, "echo"))
		return (builtin_echo);
	else if (!ft_strcmp(cmd_name, "cd"))
		return (builtin_cd);
	else if (!ft_strcmp(cmd_name, "pwd"))
		return (builtin_pwd);
	else if (!ft_strcmp(cmd_name, "export"))
		return (builtin_export);
	else if (!ft_strcmp(cmd_name, "unset"))
		return (builtin_unset);
	else if (!ft_strcmp(cmd_name, "env"))
		return (builtin_env);
	else if (!ft_strcmp(cmd_name, "exit"))
		return (builtin_exit);
	return (NULL);
}
