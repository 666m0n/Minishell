/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:17:38 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/02 10:43:40 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Format standard des erreurs: "minishell: [cmd]: [arg]: [msg]"
** Les arguments cmd et arg sont optionnels
*/
static int print_error(const char *cmd_name, const char *arg, const char *msg)
{
	if (arg)
		ft_printf(2, "minishell: %s: %s: %s\n", cmd_name, arg, msg);
	else if (cmd_name)
		ft_printf(2, "minishell: %s: %s\n", cmd_name, msg);
	else
		ft_printf(2, "minishell: %s\n", msg);
	return (ERROR);
}

/*
** Gère les erreurs de commande (command not found, permission denied, etc.)
** Retourne le code approprié selon le type d'erreur
*/
int handle_command_error(t_command *cmd, int error_code)
{
	const char *cmd_name;

	cmd_name = get_command_name(cmd);
	if (cmd_name == NULL)
		return (print_error_msg(NULL, "command not found"));
	if (error_code == CMD_NOT_FOUND)
	{
		print_error(NULL, NULL, "command not found");
		return (CMD_NOT_FOUND);
	}
	if (error_code == PERMISSION_DENIED)
	{
		print_error(cmd_name, NULL, "Permission denied");
		return (PERMISSION_DENIED);
	}
	if (error_code == IS_DIR)
	{
		print_error(cmd_name, NULL, "Is a directory");
		return (IS_DIR);
	}
	if (errno)
		print_error(cmd_name, NULL, strerror(errno));
	return (ERROR);
}

/*
** Gestion des erreurs de builtin avec support des arguments
*/
int handle_builtin_error(const char *builtin, const char *arg, const char *msg)
{
	return (print_error(builtin, arg, msg));
}

/*
** Gère les erreurs de syntaxe
** Exemple: quotes non fermées, pipes mal placés, etc.
*/
int handle_syntax_error(const char *token)
{
	if (token)
		ft_printf(2, "minishell: syntax error near unexpected token `%s'\n", token);
	else
		ft_printf(2, "minishell: syntax error\n");
	return (SYNTAX_ERROR);
}

/*
** Gère les erreurs système (fork, pipe, malloc, etc.)
** Utilise errno pour le message d'erreur
*/
int handle_system_error(const char *syscall)
{
	print_error(syscall, NULL, strerror(errno));
	if (errno == ENOMEM)
		return (MEMORY_ERROR);
	return (ERROR);
}
