/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:51:50 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/12 14:13:13 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "parsing.h"

//PATOUCHE
typedef enum e_token
{
	T_STRING,
	T_SPACE,
	T_PIPE,
	T_REDIRIN,
	T_REDIROUT,
	T_APPEND,
	T_HEREDOC,
	T_SQUOTE,
	T_DQUOTE,
	T_OPTIONS,
	T_CMD,
	T_AMPERSAND,
	T_UNKNOWN
}	t_token;

//PATOUCHE AUSSI
typedef struct s_lexer
{
	struct s_lexer	*next;
	struct s_lexer	*prev;
	char			*content;
	t_token			type;
	int				index;
}	t_lexer;

//modifier la fonction t_return type
typedef enum e_return
{
	SUCCESS = 0,
	ERROR = -1
}	t_return;

/* Basic types */
typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

/* Environment variables */
typedef struct s_env
{
	struct s_env	*next;
	char			*raw;
	char			*id;
	char			*value;
}	t_env;

/* Redirection management */
typedef struct s_redirection
{
	struct s_redirection	*next;
	char					*file;
	t_token					type;
	int						expand;
}	t_redirection;

/* FDs management */
typedef struct s_fd_state
{
	int				stdin_backup;
	int				stdout_backup;
	int				pipe_read;
	int				pipe_write;
	int				curr_in;
	int				curr_out;
	t_redirection	*last_in;
	t_redirection	*last_out;
}	t_fd_state;

/* Command structure */
typedef struct s_cmd
{
	struct s_ctx		*ctx;
	struct s_cmd		*prev;
	struct s_cmd		*next;
	t_redirection		*redirections;
	char				**args;
	char				**str;
	char				*path;
	t_fd_state			*fd;
	int					index;
	int					exit_status;
}	t_cmd;

/* Shell context */
typedef struct s_ctx
{
	t_env			*envp;
	int				def_in;
	int				def_out;
	int				interrupt_flag;
	unsigned char	exit_code;
	t_lexer			*current_token;
	struct s_cmd	*cmd;
}	t_ctx;

typedef struct s_syntax
{
	struct s_syntax	*next;
	struct s_syntax	*prev;
	char			*content;
	t_token			type;
	int				index;
}	t_syntax;

#endif