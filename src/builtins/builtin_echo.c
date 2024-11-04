/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:49:11 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/04 16:02:56 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Gère le cas où echo est appelé sans argument
** Affiche simplement un retour à la ligne
** Retourne SUCCESS
*/
static int	handle_no_args(void)
{
	write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}

/*
** Vérifie si un argument est l'option -n
** @param str: chaîne à vérifier
** @return: TRUE si c'est une option -n valide, FALSE sinon
*/
static t_bool	is_n_option(const char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (FALSE);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
** Affiche les arguments de la commande echo
** @param args: tableau d'arguments à afficher
** @param start: index de début d'affichage
*/
static void	print_args(char **args, int start)
{
	int	i;

	i = start;
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
}

/*
** Implémente la commande builtin echo de bash
** @param cmd: structure contenant la commande et ses arguments
** @param ctx: contexte d'exécution (non utilisé)
** @return: SUCCESS en cas de succès, ERROR en cas d'erreur
*/
int	builtin_echo(t_command *cmd, t_ctx *ctx)
{
	char	**args;
	t_bool	n_option;
	int		start;

	(void)ctx;
	if (!cmd || !cmd->cmd || !cmd->cmd->args)
		return (ERROR);
	args = cmd->cmd->args;
	if (!args[1])
		return (handle_no_args());
	start = 1;
	n_option = FALSE;
	while (args[start] && is_n_option(args[start]))
	{
		n_option = TRUE;
		start++;
	}
	print_args(args, start);
	if (!n_option)
		write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
