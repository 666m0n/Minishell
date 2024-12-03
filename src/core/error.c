/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:17:38 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/03 11:32:40 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Formate et affiche un message d'erreur sur stderr
** Format: "minishell: [cmd]: [arg]: [msg]"
** @param cmd_name: nom de la commande (optionnel)
** @param arg: argument concerné (optionnel)
** @param msg: message d'erreur
** @return: ERROR
*/
static int	print_error(const char *cmd_name, const char *arg, const char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd_name)
	{
		ft_putstr_fd((char *)cmd_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd((char *)arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (ERROR);
}

/*
** Gère les erreurs d'exécution de commande
** - CMD_NOT_FOUND: commande introuvable
** - PERMISSION_DENIED: pas les droits d'exécution
** - IS_DIR: tentative d'exécuter un dossier
** @param cmd: commande concernée
** @param error_code: code d'erreur
** @return: code d'erreur approprié
*/
int handle_command_error(t_cmd *cmd, int error_code)
{
    const char *cmd_name;

    cmd_name = get_cmd_name(cmd);
    if (cmd_name == NULL)
        cmd_name = "";  // Pour le cas ""

    if (error_code == CMD_NOT_FOUND)
    {
        print_error(NULL, cmd_name, "command not found");
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
** Gère les erreurs des commandes builtin
** @param builtin: nom du builtin
** @param arg: argument problématique (optionnel)
** @param msg: message d'erreur
** @return: ERROR après affichage du message
*/
int	handle_builtin_error(const char *builtin, const char *arg, const char *msg)
{
	return (print_error(builtin, arg, msg));
}

/*
** Gère les erreurs de syntaxe du shell
** @param token: token problématique (optionnel)
** @return: SYNTAX_ERROR après affichage du message
*/
int	handle_syntax_error(const char *token)
{
	if (token)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `" \
		, STDERR_FILENO);
		ft_putstr_fd((char *)token, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	else
		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
	return (SYNTAX_ERROR);
}

/*
** Gère les erreurs système (fork, pipe, malloc...)
** Utilise errno pour le message
** @param syscall: nom de l'appel système échoué
** @return: MEMORY_ERROR si plus de mémoire, ERROR sinon
*/
int	handle_system_error(const char *syscall)
{
	print_error(syscall, NULL, strerror(errno));
	if (errno == ENOMEM)
		return (MEMORY_ERROR);
	return (ERROR);
}
