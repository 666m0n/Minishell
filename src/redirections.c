/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:19:47 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/06 11:29:42 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Configure une redirection de sortie
** @param file: nom du fichier
** @param append: TRUE pour mode append (>>), FALSE pour écraser (>)
** @return: SUCCESS en cas de succès, ERROR sinon
*/
static int	setup_output_redir(char *file, t_bool append)
{
	int	fd;

	if (append == TRUE)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ERROR);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

/*
** Configure une redirection d'entrée
** @param file: nom du fichier
** @return: SUCCESS en cas de succès, ERROR sinon
*/
static int	setup_input_redir(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ERROR);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

/*
** Configure les redirections pour le processus enfant
** @param redirections: liste des redirections à appliquer
** @return: SUCCESS en cas de succès, ERROR sinon
*/
int	setup_redirections(t_redirection *redirections)
{
	t_redirection	*current;
	int				ret;

	current = redirections;
	ret = SUCCESS;
	while (current && ret == SUCCESS)
	{
		if (current->type == REDIR_IN)
			ret = setup_input_redir(current->file);
		else if (current->type == REDIR_OUT)
			ret = setup_output_redir(current->file, FALSE);
		else if (current->type == APPEND)
			ret = setup_output_redir(current->file, TRUE);
		current = current->next;
	}
	return (ret);
}
