/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:20:17 by emmmarti          #+#    #+#             */
/*   Updated: 2024/11/24 15:18:41 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Vérifie si la commande a des redirections
** @param cmd: structure de commande
** @return: TRUE si au moins une redirection, FALSE sinon
*/
t_bool	has_redirection(t_cmd *cmd)
{
	if (get_redirections(cmd) == NULL)
		return (FALSE);
	else
		return (TRUE);
}
