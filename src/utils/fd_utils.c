/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:43:39 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/09 18:43:58 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Initialise les descripteurs de fichiers d'une commande
** @param cmd: commande à initialiser
** @return: SUCCESS si ok, ERROR si erreur
** Cette fonction doit être appelée avant tout traitement de redirections
** Elle met en place les FDs par défaut (stdin/stdout) et initialise
** les sauvegardes à -1
*/
int	init_command_fds(t_simple_cmd *cmd)
{
	if (!cmd)
		return (ERROR);

	cmd->input.original = STDIN_FILENO;
	cmd->input.current = STDIN_FILENO;
	cmd->input.backup = -1;

	cmd->output.original = STDOUT_FILENO;
	cmd->output.current = STDOUT_FILENO;
	cmd->output.backup = -1;

	return (SUCCESS);
}
