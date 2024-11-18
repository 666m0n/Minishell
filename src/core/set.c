/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:47:22 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/18 18:04:53 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Met à jour le code de sortie d'une commande
** @param cmd: structure de commande
** @param status: nouveau code de sortie
*/
void	set_exit_status(t_cmd *cmd, int status)
{
	if (cmd)
		cmd->exit_status = status;
}

/*
** Définit le chemin complet de la commande
** @param cmd: structure de commande
** @param path: chemin à assigner
** @return: SUCCESS si ok, ERROR si cmd invalide
*/
int	set_cmd_path(t_cmd *cmd, char *path)
{
	if (!cmd)
		return (ERROR);
	cmd->path = path;
	return (SUCCESS);
}
