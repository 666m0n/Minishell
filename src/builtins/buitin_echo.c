/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitin_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:49:11 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/02 12:26:26 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** echo avec option -n
** Retourne 0 (SUCCESS) en cas de succès, 1 (ERROR) sinon
*/

/*
** Gère le cas où echo est appelé sans argument
** Affiche simplement un retour à la ligne
** Retourne SUCCESS
*/
static int	handle_no_args(void)
{
	ft_printf("\n");
	return (SUCCESS);
}

/*
** Vérifie si l'option -n est présente dans la commande
** @param args: tableau d'arguments de la commande
** @param i: pointeur vers l'index de traitement des arguments
** @return: TRUE si l'option -n est présente, FALSE sinon
** Si l'option est présente, incrémente i pour sauter l'argument "-n"
*/
static t_bool	check_n_option(char **args, int *i)
{
	if (args[1] == NULL)
		return (FALSE);
	if (ft_strcmp(args[1], "-n") == 0)
	{
		(*i)++;
		return (TRUE);
	}
	return (FALSE);
}

/*
** Affiche les arguments de la commande echo
** @param args: tableau d'arguments à afficher
** @param start_index: index à partir duquel commencer l'affichage
** Ajoute un espace entre chaque argument, mais pas après le dernier
*/
static void	print_args(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i] != NULL)
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
}

/*
** Implémente la commande builtin echo de bash
** @param cmd: structure contenant la commande et ses arguments
** @param ctx: contexte d'exécution (non utilisé)
** @return: SUCCESS en cas de succès, ERROR en cas d'erreur
** Gère l'option -n qui supprime le retour à la ligne final
** Affiche tous les arguments séparés par des espaces
** Ajoute un retour à la ligne final sauf si l'option -n est présente
*/
int	builtin_echo(t_command *cmd, t_ctx *ctx)
{
	char	**args;
	int		i;
	t_bool	n_option;

	(void)ctx;
	if (!cmd || !cmd->cmd || !cmd->cmd->args)
		return (ERROR);
	args = cmd->cmd->args;
	if (args[1] == NULL)
		return (handle_no_args());
	i = 1;
	n_option = check_n_option(args, &i);
	print_args(args, i);
	if (n_option == FALSE)
		ft_printf("\n");
	return (SUCCESS);
}
