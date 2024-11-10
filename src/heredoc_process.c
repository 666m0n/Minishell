/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:38:36 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/10 21:43:28 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Affiche le message d'avertissement pour EOF
** @param delimiter: délimiteur attendu
** @return: SUCCESS
*/
static int	write_eof_warning(const char *delimiter)
{
	ft_putstr_fd("bash: avertissement : « here-document » à la ligne ", 2);
	ft_putstr_fd("X", 2);
	ft_putstr_fd(" délimité par la fin du fichier ", 2);
	ft_putstr_fd("(au lieu de « ", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd(" »)\n", 2);
	return (SUCCESS);
}

/*
** Vérifie si une ligne correspond au délimiteur
** @param line: ligne à vérifier
** @param delimiter: délimiteur à comparer
** @return: TRUE si c'est le délimiteur, FALSE sinon
*/
static t_bool	is_delimiter(const char *line, const char *delimiter)
{
	if (!line)
		return (FALSE);
	return (ft_strcmp(line, delimiter) == 0);
}

/*
** Gère une ligne du heredoc
** @param heredoc: structure heredoc
** @param line: ligne lue
** @param ctx: contexte du shell
** @return: SUCCESS, CONTINUE, ou ERROR
*/
static int	handle_heredoc_line(t_heredoc *heredoc, char *line, t_ctx *ctx)
{
	char	*expanded;

	if (!line)
		return (write_eof_warning(heredoc->delimiter));
	if (is_delimiter(line, heredoc->delimiter))
	{
		free(line);
		return (SUCCESS);
	}
	if (get_heredoc_quote_mode(heredoc))
		expanded = ft_strdup(line);
	else
		expanded = expand_variables(line, ctx->envp, ctx->exit_code);
	free(line);
	if (!expanded)
		return (ERROR);
	if (heredoc->pipe_fd[1] != -1)
	{
		if (write(heredoc->pipe_fd[1], expanded, ft_strlen(expanded)) == -1
			|| write(heredoc->pipe_fd[1], "\n", 1) == -1)
		{
			free(expanded);
			return (ERROR);
		}
	}
	free(expanded);
	return (CONTINUE);
}

/*
** Traite un heredoc
** @param heredoc: structure heredoc à traiter
** @param ctx: contexte du shell
** @return: SUCCESS ou ERROR
*/
int	process_heredoc(t_heredoc *heredoc, t_ctx *ctx)
{
	char	*line;
	int		ret;

	if (heredoc->pipe_fd[1] == -1 && pipe(heredoc->pipe_fd) == -1)
		return (ERROR);
	ctx->curr_pipeline->in_heredoc = TRUE;
	while (1)
	{
		line = readline("> ");
		ret = handle_heredoc_line(heredoc, line, ctx);
		if (ret != CONTINUE)
			break ;
	}
	ctx->curr_pipeline->in_heredoc = FALSE;
	if (heredoc->pipe_fd[1] != -1)
		close(heredoc->pipe_fd[1]);
	if (ret == ERROR && heredoc->pipe_fd[0] != -1)
	{
		close(heredoc->pipe_fd[0]);
		heredoc->pipe_fd[0] = -1;
	}
	return (ret);
}
