/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:17:00 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/11 18:44:30 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Crée le nom d'un fichier temporaire unique
** @return: nom du fichier alloué ou NULL si erreur
** Note: incrémente le compteur jusqu'à trouver un nom disponible
*/
static char	*generate_temp_filename(void)
{
	static int	count = 0;
	char		*number;
	char		*name;

	while (1)
	{
		number = ft_itoa(count++);
		if (!number)
			return (NULL);
		name = ft_strjoin(".heredoc_", number);
		free(number);
		if (!name)
			return (NULL);
		if (access(name, F_OK) == -1)
			return (name);
		free(name);
	}
}

/*
** Crée un fichier temporaire unique pour un heredoc
** @return: chemin du fichier créé ou NULL si erreur
** Note: le fichier est créé avec les permissions 0600
*/
char	*create_temp_file(void)
{
	char	*temp_name;
	int		fd;

	temp_name = generate_temp_filename();
	if (!temp_name)
		return (NULL);
	fd = open(temp_name, O_CREAT | O_RDWR | O_EXCL, 0600);
	if (fd == -1)
	{
		free(temp_name);
		return (NULL);
	}
	close(fd);
	return (temp_name);
}

/*
** Traite un heredoc individuel et met à jour sa redirection
** @param redir: structure de redirection à traiter
** @return: SUCCESS si ok, code d'erreur sinon
*/
static int	process_single_heredoc(t_redirection *redir)
{
	char	*temp_file;
	int		status;

	temp_file = create_temp_file();
	if (!temp_file)
		return (MEMORY_ERROR);
	status = handle_single_heredoc(redir->file, temp_file);
	if (status != SUCCESS)
	{
		free(temp_file);
		return (status);
	}
	free(redir->file);
	redir->file = temp_file;
	return (SUCCESS);
}

/*
** Parcourt et traite tous les heredocs d'une commande dans l'ordre
** @param cmd: structure de commande contenant les redirections
** @return: SUCCESS si ok, code d'erreur sinon
*/
int	process_heredocs(t_cmd *cmd)
{
	t_redirection	*redir;
	int				status;
	t_cmd			*current;

	current = cmd;
	while (current)
	{
		if (current->redirections)
		{
			redir = current->redirections;
			while (redir)
			{
				if (redir->type == T_HEREDOC)
				{
					status = process_single_heredoc(redir);
					if (status != SUCCESS)
						return (status);
				}
				redir = redir->next;
			}
		}
		current = current->next;
	}
	return (SUCCESS);
}
