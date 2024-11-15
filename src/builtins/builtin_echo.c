/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:49:11 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/15 11:03:39 by emmanuel         ###   ########.fr       */
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
** Vérifie si un argument est une option -n valide (-n, -nn, -nnn, etc.)
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
** Affiche les arguments de la commande echo avec un espace entre chaque argument
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
** Implémente la commande echo
** - Gère l'option -n (pas de retour à la ligne)
** - Affiche les arguments séparés par un espace
** - Si pas d'option -n, ajoute un retour à la ligne à la fin
** @param cmd: structure contenant la commande et ses arguments
** @param ctx: contexte d'exécution (non utilisé)
** @return: SUCCESS ou ERROR
*/
int	builtin_echo(t_cmd *cmd, t_ctx *ctx)
{
	char	**args;
	t_bool	n_option;
	int		start;

	(void)ctx;
	if (!cmd || !cmd->args)
		return (ERROR);
	args = cmd->args;
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
