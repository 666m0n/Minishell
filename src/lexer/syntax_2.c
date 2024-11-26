/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:47:18 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/26 15:08:37 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (666);
	}
	return (SUCCESS);
}
