/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:20:17 by emmmarti          #+#    #+#             */
/*   Updated: 2024/11/12 13:11:21 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	has_redirection(t_cmd *cmd)
{
	if (get_redirections(cmd) == NULL)
		return (FALSE);
	else
		return (TRUE);
}
