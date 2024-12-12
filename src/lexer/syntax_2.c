/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:47:18 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/12 13:39:29 by sviallon         ###   ########.fr       */
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
	if (ft_strcmp(content, "$HOME") == 0)
		return (1);
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

static int	print_dir_error(char *content)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(content, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	return (IS_DIR);
}

int	is_env_var_dir(char *content, t_ctx *data)
{
	char	*value;

	if (!content || content[0] != '$')
		return (0);
	value = get_env_value(data->envp, content + 1);
	if (!value || !*value)
		return (0);
	return (is_directory(value));
}

int	handle_misc(t_syntax *token, t_ctx *data)
{
	char	*expanded;

	if ((token->content[0] == '#' || token->content[0] == '!'
			|| token->content[0] == ':') && token->content[1] == '\0')
	{
		if (token->content[0] == '!')
			return (ERROR);
		return (69);
	}
	if (!ft_strcmp(token->content, "$HOME"))
	{
		expanded = get_env_value(data->envp, "HOME");
		if (!expanded || !*expanded)
			return (ERROR);
		return (print_dir_error(expanded));
	}
	return (print_dir_error(token->content));
}
