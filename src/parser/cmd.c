/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:31:54 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/12 16:20:41 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_tab(char *str)
{
	char	**new_tab;

	new_tab = ft_calloc(sizeof(char *), 2);
	if (!new_tab)
		exit_error("Calloc failed");
	new_tab[0] = ft_strdup(str);
	new_tab[1] = NULL;
	return (new_tab);
}

static void	add_to_tab(char *str, t_cmd *cmd)
{
	char	**tmp_tab;
	int		i;
	int		count;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
		tmp_tab = ft_calloc(sizeof(char *), count + 2);
		if (!tmp_tab)
			exit_error("Calloc failed");
		i = 0;
		while (i < count)
		{
			tmp_tab[i] = cmd->args[i];
			i++;
		}
		tmp_tab[i] = ft_strdup(str);
		tmp_tab[i + 1] = NULL;
		free(cmd->args);
		cmd->args = tmp_tab;
	}
	else
		cmd->args = create_tab(str);
}

static char	*copy_str(char *str, t_token **tok)
{
	str = ft_strdup((*token)->content);
	if (!str)
		return (NULL);
	while ((*token)->next && is_cmd((*token)->next->type))
	{
		str = ft_stjoin(str, (*token)->next->token);
		if (!str)
			return (NULL);
		(*token) = (*token)->next;
	}
	return (str);
}

void	process_pars(t_cmd *cmd, t_lexer *token, t_ctx *data)
{
	char	*tmp;

	while (token)
	{
		if (is_cmd(token->type))
		{
			if (!token->content || token->content[0] == '\0')
			{
				token = token->next;
				continue ;
			}
			tmp = copy_str(tmp, &token);
			add_to_tab(tmp, cmd);
			free(tmp);
		}
		else if (token->type == T_PIPE)
			extend_cmd(&cmd, data);
		else if (is_redir(token->type))
			handle_redir(cmd, &token);
		token = token->next;
	}
}
