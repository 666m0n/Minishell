/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:17:38 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/12 13:46:27 by emmmarti         ###   ########.fr       */
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
** Gère l'erreur CMD_NOT_FOUND
** Affiche le message approprié selon la présence de PATH
** @param cmd_name : nom de la commande non trouvée
** @param env : variables d'environnement pour vérifier PATH
** @return : code d'erreur CMD_NOT_FOUND
*/
static int	handle_not_found_error(const char *cmd_name, t_env *env)
{
	if (!get_env_value(env, "PATH"))
		print_error(cmd_name, NULL, "No such file or directory");
	else
		print_error(NULL, cmd_name, "command not found");
	return (CMD_NOT_FOUND);
}

/*
** Gère les erreurs de type permissions et dossier
** Affiche le message d'erreur correspondant
** @param cmd_name : nom de la commande
** @param error_code : code d'erreur spécifique à traiter
** @return : code d'erreur correspondant ou ERROR
*/
static int	handle_specific_error(const char *cmd_name, int error_code)
{
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
	return (ERROR);
}

/*
** Point d'entrée principal pour la gestion des erreurs de commande
** Redirige vers les handlers spécifiques ou gère errno
** @param cmd : commande ayant échoué
** @param error_code : code d'erreur à traiter
** @return : code d'erreur approprié pour le shell
*/
int	handle_command_error(t_cmd *cmd, int error_code)
{
	const char	*cmd_name;

	cmd_name = get_cmd_name(cmd);
	if (!cmd_name)
		cmd_name = "";
	if (error_code == CMD_NOT_FOUND)
		return (handle_not_found_error(cmd_name, cmd->ctx->envp));
	if (error_code == PERMISSION_DENIED || error_code == IS_DIR)
		return (handle_specific_error(cmd_name, error_code));
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
