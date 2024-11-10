/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:25:57 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/10 20:31:09 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Vérifie si le délimiteur d'un heredoc contient des quotes
** @param ctx: contexte du shell
** @return: TRUE si le délimiteur contient des quotes, FALSE sinon
** Note: La présence de quotes (simples ou doubles) désactive l'expansion
*/
t_bool	get_heredoc_quote_mode(t_ctx *ctx)
{
	t_heredoc	*current;
	char		*delimiter;

	if (!ctx || !ctx->pend_heredocs || !ctx->pend_heredocs->delimiter)
		return (FALSE);
	current = ctx->pend_heredocs;
	delimiter = current->delimiter;
	while (*delimiter)
	{
		if (*delimiter == '\'' || *delimiter == '"')
			return (TRUE);
		delimiter++;
	}
	return (FALSE);
}
