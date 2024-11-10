/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:20:48 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/10 10:36:18 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

/*
** Récupère la liste des redirections d'une commande
** @param cmd: structure de commande
** @return: liste des redirections ou NULL si invalide
*/
t_redirection	*get_redirections(t_command *cmd)
{
	if (!cmd || !cmd->cmd)
		return (NULL);
	return (cmd->cmd->redirections);
}

/*
** Récupère le pipeline actuel du contexte
** @param ctx: contexte du shell
** @return: pipeline actuel ou NULL si invalide
*/
t_pipeline	*get_current_pipeline(t_ctx *ctx)
{
	if (!ctx)
		return (NULL);
	return (ctx->curr_pipeline);
}

/*
** Récupère la liste des heredocs en attente
** @param ctx: contexte du shell
** @return: liste des heredocs ou NULL si invalide
*/
t_heredoc	*get_pending_heredocs(t_ctx *ctx)
{
	if (!ctx)
		return (NULL);
	return (ctx->pend_heredocs);
}

/*
** Récupère l'état d'interruption du contexte
** @param ctx: contexte du shell
** @return: flag d'interruption ou 0 si invalide
*/
int	get_interrupt_flag(t_ctx *ctx)
{
	if (!ctx)
		return (0);
	return (ctx->interrupt_flag);
}

/*
** Récupère le descripteur de fichier d'entrée par défaut
** @param ctx: contexte du shell
** @return: fd d'entrée ou -1 si invalide
*/
int	get_default_input(t_ctx *ctx)
{
	if (!ctx)
		return (-1);
	return (ctx->def_in);
}
