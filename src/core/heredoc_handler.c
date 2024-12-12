/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:37:26 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/12 19:07:14 by sviallon         ###   ########.fr       */
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
/* static char	*read_heredoc_line(const char *delimiter,
			 t_ctx *data, int *status)
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
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
} */

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
/* static int	heredoc_to_file(int fd, const char *delimiter,
	int should_expand, t_ctx *data)
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
		if (g_sig_status == SIGINT)
		{
			free(line);
			close(fd);
			setup_interactive_signals();
			return (130);
		}
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
} */

static void	report_heredoc_eof_warning(const char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd((char *)delimiter, 2);
	ft_putstr_fd("')\n", 2);
	exit(0);
}

static void	process_heredoc_content(int fd, const char *delimiter,
			int should_expand, t_ctx *data)
{
	char	*line;
	char	*expanded_line;
	
	setup_heredoc_signals();
	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
		{
			report_heredoc_eof_warning(delimiter);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			exit(0);
		}
		if (should_expand && ft_strchr(line, '$'))
		{
			expanded_line = expand_heredoc_line(line, data);
			write_heredoc_line(fd, expanded_line);
			free(expanded_line);
		}
		else
			write_heredoc_line(fd, line);
		free(line);
		}
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
	pid_t	pid;
	int		fd;
	int		status;

	fd = open(file, O_WRONLY);
	if (fd == -1)
		return (handle_system_error("open"));
	pid = fork();
	if (pid == -1)
		return (handle_system_error("fork"));
	if (pid == 0)
		process_heredoc_content(fd, delimiter, should_expand, data);
	waitpid(pid, &status, 0);
	close(fd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (130);
}
