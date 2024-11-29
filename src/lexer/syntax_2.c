/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Simon <Simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:47:18 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/27 15:55:59 by Simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_exit_code(int status, t_ctx *data)
{
	if (status == 69)
	{
		data->exit_code = 0;
		return ;
	}
	else
	{
		data->exit_code = status;
		return ;
	}
}

int	is_directory(const char *content)
{
	int	i;
	int	found_char;

	if (!content || !*content)
		return (0);
	i = 0;
	found_char = 0;
	while (content[i])
	{
		if (content[i] != '/' && content[i] != '.')
			return (0);
		if (content[i] == '/' || content[i] == '.')
			found_char = 1;
		i++;
	}
	return (found_char);
}

int	handle_misc(t_syntax *token)
{
	if (is_directory(token->content))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(token->content, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		return (126);
	}
	else if ((token->content[0] == '#' || token->content[0] == '!'
			|| token->content[0] == ':') && token->content[1] == '\0')
	{
		if (token->content[0] == '!')
			return (ERROR);
		else
			return (69);
	}
	return (SUCCESS);
}
