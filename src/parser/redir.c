/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:16:13 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/11 17:15:35 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* void	handle_redir(t_cmd *cmd, t_lexer **tokens)
{
	t_lexer			*new_tok;
	t_token			type;

	if (!tokens || !(*tokens) || !(*tokens)->next)
		return ;
	type = (*tokens)->type;
	if ((*tokens)->next->type == T_SPACE && (*tokens)->next->next)
		(*tokens) = (*tokens)->next->next;
	else if ((*tokens)->next)
		(*tokens) = (*tokens)->next;
	if (!is_cmd((*tokens)->type))
		return ;
	new_tok = create_token((*tokens)->content,
			ft_strlen((*tokens)->content), type);
	if (!new_tok)
		exit_error("create_token failed");
	if (cmd->redirections)
		add_token(&(cmd->redirections), new_tok);
	else
		cmd->redirections = new_tok;
} */

static t_redirection	*create_redir(t_token type, char *file)
{
	t_redirection	*new;

	new = ft_calloc(1, sizeof(t_redirection));
	if (!new)
		exit_error("malloc failed");
	new->type = type;
	new->file = ft_strdup(file);
	if (!new->file)
	{
		free(new);
		exit_error("malloc failed");
	}
	new->next = NULL;
	return (new);
}

/* void	handle_redir(t_cmd *cmd, t_lexer **tokens)
{
	t_lexer		*new_tok;
	t_token		type;

	if (!tokens || !(*tokens) || !(*tokens)->next)
		return ;
	type = (*tokens)->type;
	if ((*tokens)->next->type == T_SPACE)
	{
		if (!(*tokens)->next->next)
			return ;
		(*tokens) = (*tokens)->next->next;
	}
	else
		(*tokens) = (*tokens)->next;
	if (!is_cmd((*tokens)->type))
		return ;
	new_tok = create_redir(type, (*tokens)->content);
	if (cmd->redirections)
	{
		t_redirection *tmp = cmd->redirections;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_tok;
	}
	else
		cmd->redirections = new_tok;
} */

void	handle_redir(t_cmd *cmd, t_lexer **tokens)
{
    t_redirection    *new_tok;
    t_token          type;
    t_redirection    *tmp;

    if (!tokens || !(*tokens))
        return ;
    type = (*tokens)->type;
    // Vérifier l'existence d'un token suivant avant d'y accéder
    if (!(*tokens)->next)
        return ;
    // Gérer le cas avec espace de manière plus sûre
    if ((*tokens)->next->type == T_SPACE)
    {
        if (!(*tokens)->next->next)  // Pas de token après l'espace
            return ;
        *tokens = (*tokens)->next->next;
    }
    else
        *tokens = (*tokens)->next;
    // Vérifier que le token restant est valide pour un nom de fichier
    if (!is_cmd((*tokens)->type))
        return ;
    // Créer et ajouter la redirection
    new_tok = create_redir(type, (*tokens)->content);
    if (!new_tok)
        return ;
    // Ajouter à la fin de la liste des redirections
    if (cmd->redirections)
    {
        tmp = cmd->redirections;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_tok;
    }
    else
        cmd->redirections = new_tok;
}
