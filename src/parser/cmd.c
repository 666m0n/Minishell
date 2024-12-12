/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:31:54 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/12 10:37:42 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static char	**create_tab(char *str)
{
	char	**new_tab;

	new_tab = ft_calloc(sizeof(char *), 2);
	if (!new_tab)
		exit_error("Calloc failed");
	new_tab[0] = ft_strdup(str);
	new_tab[1] = NULL;
	return (new_tab);
} */

static void	free_tab_complete(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**create_new_args(char **old_args, int size)
{
	char	**new_tab;
	int		i;

	new_tab = ft_calloc(sizeof(char *), (size + 2));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_tab[i] = ft_strdup(old_args[i]);
		if (!new_tab[i])
		{
			free_tab_partial(new_tab, i);
			return (NULL);
		}
		i++;
	}
	return (new_tab);
}

void	add_to_tab(char *str, t_cmd *cmd)
{
	char	**new_tab;
	int		size;

	if (!str || !cmd)
		return ;
	size = 0;
	if (cmd->args)
		while (cmd->args[size])
			size++;
	new_tab = create_new_args(cmd->args, size);
	if (!new_tab)
		return ;
	new_tab[size] = ft_strdup(str);
	if (!new_tab[size])
	{
		free_tab_partial(new_tab, size);
		return ;
	}
	new_tab[size + 1] = NULL;
	if (cmd->args)
		free_tab_complete(cmd->args);
	cmd->args = new_tab;
}

/* static char	*copy_str(char *str, t_lexer **tokens)
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
} */

static char	*concatenate_quotes(t_lexer **tokens)
{
	char	*result;
	char	*temp;
	char	*new_str;

	result = ft_strdup((*tokens)->content);
	if (!result)
		return (NULL);
	while ((*tokens)->next && (is_cmd((*tokens)->next->type)
			|| (*tokens)->next->type == T_SQUOTE
			|| (*tokens)->next->type == T_DQUOTE))
	{
		temp = result;
		new_str = ft_strjoin(result, (*tokens)->next->content);
		if (!new_str)
		{
			free(temp);
			return (NULL);
		}
		result = new_str;
		free(temp);
		*tokens = (*tokens)->next;
	}
	return (result);
}

void	process_pars(t_cmd *cmd, t_lexer *tokens, t_ctx *data)
{
	char	*content;

	while (tokens)
	{
		if (is_cmd(tokens->type) || tokens->type == T_SQUOTE
			|| tokens->type == T_DQUOTE)
		{
			content = concatenate_quotes(&tokens);
			if (content)
			{
				add_to_tab(content, cmd);
				free(content);
			}
		}
		else if (tokens->type == T_PIPE)
			extend_cmd(&cmd, data);
		else if (is_redir(tokens->type))
			handle_redir(cmd, &tokens);
		tokens = tokens->next;
	}
}
