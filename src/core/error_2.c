/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:57:30 by emmmarti          #+#    #+#             */
/*   Updated: 2024/12/12 18:58:34 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Gère les erreurs de syntaxe du shell
** @param token: token problématique (optionnel)
** @return: SYNTAX_ERROR après affichage du message
*/
int	handle_syntax_error(const char *token)
{
	if (token)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `" \
		, STDERR_FILENO);
		ft_putstr_fd((char *)token, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	else
		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
	return (SYNTAX_ERROR);
}

/*
** Gère les erreurs système (fork, pipe, malloc...)
** Utilise errno pour le message
** @param syscall: nom de l'appel système échoué
** @return: MEMORY_ERROR si plus de mémoire, ERROR sinon
*/
int	handle_system_error(const char *syscall)
{
	print_error(syscall, NULL, strerror(errno));
	if (errno == ENOMEM)
		return (MEMORY_ERROR);
	return (ERROR);
}
