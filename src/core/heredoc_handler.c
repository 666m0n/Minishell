/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:37:26 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/11 18:45:10 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Écrit une ligne dans le fichier heredoc
** @param fd: descripteur du fichier
** @param line: ligne à écrire
** @return: SUCCESS si ok, code d'erreur sinon
*/
int	write_heredoc_line(int fd, const char *line)
{
	if (write(fd, line, ft_strlen(line)) == -1)
		return (handle_system_error("write"));
	if (write(fd, "\n", 1) == -1)
		return (handle_system_error("write"));
	return (SUCCESS);
}

/*
** Lit une ligne du heredoc et vérifie si c'est le délimiteur
** @param delimiter: chaîne qui termine le heredoc
** @return: ligne lue ou NULL si délimiteur ou erreur
*/
static char	*read_heredoc_line(const char *delimiter)
{
	char	*line;

	line = readline(HEREDOC_PROMPT);
	if (!line || ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static int	heredoc_to_file(int fd, const char *delimiter)
{
	char	*line;
	int		status;

	status = SUCCESS;
	while (status == SUCCESS)
	{
		line = read_heredoc_line(delimiter);
		if (!line)
			break ;
		status = write_heredoc_line(fd, line);
		free(line);
	}
	return (status);
}

/*
** Gère un heredoc : lit l'entrée jusqu'au délimiteur et l'écrit dans le fichier
** @param delimiter: chaîne qui termine le heredoc
** @param file: chemin du fichier où écrire le contenu
** @return: SUCCESS si ok, code d'erreur sinon
*/
int	handle_single_heredoc(const char *delimiter, const char *file)
{
	int		fd;
	int		status;

	fd = open(file, O_WRONLY);
	if (fd == -1)
		return (handle_system_error("open"));
	status = heredoc_to_file(fd, delimiter);
	close(fd);
	return (status);
}
