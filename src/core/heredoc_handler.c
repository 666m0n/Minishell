/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:37:26 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/12 16:16:45 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_heredoc_line(char *line, t_ctx *data)
{
	char	*expanded;
	size_t	i;

	if (!line)
		return (NULL);
	i = 0;
	expanded = replace_var(line, data, &i);
	if (!expanded)
		return (ft_strdup(line));
	return (expanded);
}

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
static char	*read_heredoc_line(const char *delimiter, t_ctx *data, int *status)
{
	char	*line;

	(void)data;
	*status = SUCCESS;
	line = readline(HEREDOC_PROMPT);
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document ", 2);
		ft_putstr_fd("delimited by end-of-file (wanted `", 2);
		ft_putstr_fd((char *)delimiter, 2);
		ft_putstr_fd("')\n", 2);
		return (NULL);
	}
	if (g_sig_status == SIGINT)
	{
		free(line);
		*status = 130;
		return (NULL);
	}
	add_history(line);
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/*
** Lit et écrit le contenu du heredoc dans le fichier
** @param fd: descripteur du fichier
** @param delimiter: chaîne qui termine le heredoc
** @return: SUCCESS si ok, code d'erreur sinon
*/
/* static int	heredoc_to_file(int fd, const char *delimiter)
{
	char	*line;
	int		status;

	setup_heredoc_signals();
	status = SUCCESS;
	while (status == SUCCESS && g_sig_status == 0)
	{
		line = read_heredoc_line(delimiter);
		if (!line || g_sig_status == SIGINT)
			status = ERROR;
		else if (line)
			status = write_heredoc_line(fd, line);
		free(line);
		if (!line)
			break ;
	}
	setup_interactive_signals();
	return (status);
} */

/* heredoc_handler.c */
static int	heredoc_to_file(int fd, const char *delimiter, int should_expand, t_ctx *data)
{
	char	*line;
	char	*expanded_line;
	int		status;

	setup_heredoc_signals();
	status = SUCCESS;
	while (status == SUCCESS)
	{
		line = read_heredoc_line(delimiter, data, &status);
		if (!line)
			break ;
		if (should_expand && ft_strchr(line, '$'))
		{
			expanded_line = expand_heredoc_line(line, data);
			status = write_heredoc_line(fd, expanded_line);
			free(expanded_line);
		}
		else
			status = write_heredoc_line(fd, line);
		free(line);
	}
	setup_interactive_signals();
	return (status);
}

/*
** Gère un heredoc : lit l'entrée jusqu'au délimiteur et l'écrit dans le fichier
** @param delimiter: chaîne qui termine le heredoc
** @param file: chemin du fichier où écrire le contenu
** @return: SUCCESS si ok, code d'erreur sinon
*/
int	handle_single_heredoc(const char *delimiter, const char *file,
		int should_expand, t_ctx *data)
{
	int		fd;
	int		status;

	fd = open(file, O_WRONLY);
	if (fd == -1)
		return (handle_system_error("open"));
	status = heredoc_to_file(fd, delimiter, should_expand, data);
	close(fd);
	return (status);
}
