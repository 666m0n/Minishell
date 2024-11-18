/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:54:02 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/18 18:03:17 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Implémente la commande exit sans options
** Affiche "exit" et quitte avec le dernier code de sortie
** @param cmd: structure commande (non utilisé)
** @param ctx: contexte shell pour le code de sortie
** @return: ne retourne jamais, termine le processus
*/
int	builtin_exit(t_cmd *cmd, t_ctx *ctx)
{
	(void)cmd;

	if (!ctx)
		exit(ERROR);
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(ctx->exit_code);
}
