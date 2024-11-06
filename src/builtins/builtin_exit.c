/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:54:02 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/05 12:00:49 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>

/*
** Vérifie si une chaîne représente un nombre valide
** @param str: chaîne à vérifier
** @return: TRUE si la chaîne est un nombre valide, FALSE sinon
** Un nombre valide peut commencer par + ou - et ne contient que des chiffres
*/
static t_bool	is_valid_number(const char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0')
		return (FALSE);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (FALSE);
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
** Convertit une chaîne en long en gérant les dépassements
** @param str: chaîne à convertir
** @param overflow: pointeur pour indiquer un dépassement
** @return: valeur convertie
*/
static long	ft_atol(const char *str, t_bool *overflow)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	*overflow = FALSE;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
		{
			*overflow = TRUE;
			return (0);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

/*
** Affiche un message d'erreur pour exit
** @param msg: message d'erreur
** @param arg: argument optionnel à inclure dans le message
*/
static void	print_exit_error(const char *msg, const char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (arg != NULL)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}

/*
** Termine le programme avec le code approprié
** @param arg: argument numérique à utiliser comme code de sortie
*/
static void	handle_numeric_exit(const char *arg)
{
	long	exit_code;
	t_bool	overflow;

	exit_code = ft_atol(arg, &overflow);
	if (overflow == TRUE)
	{
		print_exit_error("numeric argument required", arg);
		exit(2);
	}
	exit((unsigned char)exit_code);
}

/*
** Gère le cas où exit a plusieurs arguments
** @param args: tableau d'arguments
** @return: ERROR si trop d'arguments, ne retourne pas sinon
*/
static int	handle_multiple_args(char **args)
{
	if (is_valid_number(args[1]) == FALSE)
	{
		print_exit_error("numeric argument required", args[1]);
		exit(2);
	}
	print_exit_error("too many arguments", NULL);
	return (ERROR);
}

/*
** Vérifie si la commande est valide
** @param cmd: structure de commande à vérifier
** @return: TRUE si la commande est valide, FALSE sinon
*/
static t_bool	is_valid_command(t_command *cmd)
{
	if (cmd == NULL)
		return (FALSE);
	if (cmd->cmd == NULL)
		return (FALSE);
	if (cmd->cmd->args == NULL)
		return (FALSE);
	return (TRUE);
}

/*
** Implémente la commande builtin exit de bash
** @param cmd: structure contenant la commande et ses arguments
** @param ctx: contexte d'exécution
** @return: ne retourne jamais si l'exit réussit, ERROR sinon
*/
int	builtin_exit(t_command *cmd, t_ctx *ctx)
{
	char	**args;

	if (is_valid_command(cmd) == FALSE)
		return (ERROR);
	args = cmd->cmd->args;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (args[1] == NULL)
		exit(ctx->exit_code);
	if (args[2] != NULL)
		return (handle_multiple_args(args));
	if (is_valid_number(args[1]) == FALSE)
	{
		print_exit_error("numeric argument required", args[1]);
		exit(2);
	}
	handle_numeric_exit(args[1]);
	return (ERROR);
}
