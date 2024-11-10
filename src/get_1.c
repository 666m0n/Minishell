/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:18:17 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/10 10:36:13 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Récupère le nom de la commande
** @param cmd: structure de commande
** @return: nom de la commande ou NULL si invalide
*/
const char	*get_command_name(t_command *cmd)
{
	if (!cmd || !cmd->cmd || !cmd->cmd->args || !cmd->cmd->args[0])
		return (NULL);
	return (cmd->cmd->args[0]);
}

/*
** Récupère le statut de sortie d'une commande
** @param cmd: structure de commande
** @return: code de sortie ou ERROR si invalide
*/
int	get_command_status(t_command *cmd)
{
	if (!cmd)
		return (ERROR);
	return (cmd->exit_status);
}

/*
** Récupère le chemin complet d'une commande
** @param cmd: structure de commande
** @return: chemin de la commande ou NULL si invalide
*/
char	*get_command_path(t_command *cmd)
{
	if (!cmd || !cmd->cmd)
		return (NULL);
	return (cmd->cmd->path);
}

/*
** Vérifie si la commande est un builtin
** @param cmd: structure de commande
** @return: TRUE si builtin, FALSE sinon
*/
t_bool	get_is_builtin(t_command *cmd)
{
	if (!cmd || !cmd->cmd)
		return (FALSE);
	return (cmd->cmd->is_builtin);
}

/*
** Récupère les arguments d'une commande
** @param cmd: structure de commande
** @return: tableau d'arguments ou NULL si invalide
*/
char	**get_command_args(t_command *cmd)
{
	if (!cmd || !cmd->cmd)
		return (NULL);
	return (cmd->cmd->args);
}
