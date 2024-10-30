/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:19:40 by emmmarti          #+#    #+#             */
/*   Updated: 2024/10/30 16:16:38 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINSHELL_H

# include "../include/libft.h"
# include <sys/types.h>

# define SUCCESS 0
# define ERROR 1
# define MISUSE 2
# define CANT_EXECUTE 126
# define IS_DIR 126
# define PERMISSION_DENIED 126
# define CMD_NOT_FOUND 127
# define EXIT_CTRL_C 130
# define EXIT_CTRL_BS 131
# define EXIT_RANGE_ERR 255


typedef enum e_token
{
	CMD,
	STRING,
	ESPACE,
	VAR,
	APPEND,
	INFILE,
	OUTFILE,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	D_QUOTE,
	S_QUOTE,
	PIPE
}	t_token;

// implementer le prev utile pour la gestion d'erreur,
// pour l'expand dans le heredoc
typedef struct s_pars_node
{
	t_token				type;
	char				*content;
	struct s_pars_node	*next;
	struct s_ctx		*ctx;
}	t_pars_node;

typedef struct s_pars_list
{
	t_pars_node	*start;
	t_pars_node	*end;
	int			length;
}	t_pars_list;

typedef struct s_redirection
{
	t_token					type;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_simple_cmd
{
	char				**args;
	char				*path;
	t_redirection		*redirections;
	struct s_simple_cmd	*pipe;
}	t_simple_cmd;

typedef struct s_command
{
	t_simple_cmd	*cmd;
	int				exit_status;
}	t_command;


#endif
