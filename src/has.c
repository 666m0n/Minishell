/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:20:17 by emmmarti          #+#    #+#             */
/*   Updated: 2024/11/11 16:34:25 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	has_redirection(t_command *cmd)
{
	if (get_redirections(cmd) == NULL)
		return (FALSE);
	else
		return (TRUE);
}
