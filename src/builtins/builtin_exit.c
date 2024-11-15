/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:54:02 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/15 11:07:26 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>

/*
** Vérifie si une chaîne représente un nombre valide pour exit
** @param str: chaîne à vérifier
** @return: TRUE si nombre valide (peut commencer par +/-), FALSE sinon
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
** Convertit une chaîne en long en détectant les dépassements
** @param str: chaîne à convertir
** @param overflow: pointeur pour signaler un dépassement
** @return: valeur convertie, 0 si dépassement
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
** Affiche un message d'erreur pour la commande exit sur stderr
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
** Termine le shell avec le code de sortie approprié
** @param arg: argument numérique à utiliser comme code de sortie
** Note: ne retourne jamais, termine le processus
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
** Si le premier n'est pas un nombre : quitte avec code 2
** Sinon : affiche erreur "too many arguments" et continue le shell
** @param args: tableau d'arguments
** @return: ERROR si trop d'arguments, ne retourne pas si quitte
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
** Vérifie si la structure de commande est valide
** @param cmd: structure de commande à vérifier
** @return: TRUE si la commande est valide, FALSE si NULL ou args NULL
*/
static t_bool	is_valid_command(t_cmd *cmd)
{
	if (!cmd || !cmd->args )
		return (FALSE);
	return (TRUE);
}

/*
** Implémente la commande exit
** - Sans arg : quitte avec dernier code de sortie
** - Un arg numérique : quitte avec ce code
** - Arg non numérique : erreur (code 2)
** - Plusieurs args : erreur si premier non numérique, sinon continue
** @param cmd: structure commande
** @param ctx: contexte shell
** @return: ne retourne que si erreur
*/
int	builtin_exit(t_cmd *cmd, t_ctx *ctx)
{
	char	**args;

	if (is_valid_command(cmd) == FALSE)
		return (ERROR);
	args = cmd->args;
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
