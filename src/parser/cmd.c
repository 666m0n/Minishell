/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:31:54 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/11 18:30:49 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmd(t_token type)
{
	if (type == T_SQUOTE || type == T_DQUOTE
		|| type == T_STRING || type == T_CMD || type == T_OPTIONS)
		return (TRUE);
	return (FALSE);
}

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

static char	*copy_str(char *str, t_lexer **tokens)
{
	char	*new_str;
	char	*tmp;

	str = ft_strdup((*tokens)->content);
	if (!str)
		return (NULL);
	while ((*tokens)->next && is_cmd((*tokens)->next->type))
	{
		tmp = str;
		new_str = ft_strjoin(str, (*tokens)->next->content);
		free(tmp);
		if (!new_str)
			return (NULL);
		str = new_str;
		(*tokens) = (*tokens)->next;
	}
	return (str);
}

void	process_pars(t_cmd *cmd, t_lexer *tokens, t_ctx *data)
{
	char	*tmp;

	while (tokens)
	{
		if (is_cmd(tokens->type))
		{
			if ((!tokens->content && tokens->type != T_DQUOTE)
				|| (tokens->content[0] == '\0' && tokens->type != T_DQUOTE))
			{
				tokens = tokens->next;
				continue ;
			}
			tmp = copy_str(tmp, &tokens);
			if (tmp)
			{
				add_to_tab(tmp, cmd);
				free(tmp);
			}
		}
		else if (tokens->type == T_PIPE)
            extend_cmd(&cmd, data);
		else if (is_redir(tokens->type))
			handle_redir(cmd, &tokens);
		tokens = tokens->next;
	}
}
