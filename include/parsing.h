/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:55:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/12 11:46:25 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types.h"

# define QUOTE_ERROR "syntax error : missing quote\n"
# define IS_TOKEN "\"'|<>&"
# define IS_REDIRECTION "<>"

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

typedef struct s_lexer
{
	t_token			type;
	char			*content;
	int				index;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_redirection
{
	t_token					type;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_simple_cmd
{
	char				**args;
	t_redirection		*redirections;
	struct s_simple_cmd	*pipe;
}	t_simple_cmd;

typedef struct s_command
{
	t_simple_cmd	*cmd; // premiere cmd
	int				exit_status; // pour gerer $?
}	t_command;

//lexer



//parser

t_simple_cmd	*new_simple_cmd(void);
void			free_simple_cmd(t_simple_cmd *cmd);
void			free_command(t_command *cmd);
int				handle_argument(t_simple_cmd *cmd, t_token *token);
t_command		*parser(t_token *tokens);
void			free_redirection(t_redirection *redir);
void			add_redirection(t_simple_cmd *cmd, t_redirection *new_redir);
int				is_redirection(t_token_type type);
int				handle_redirection(t_simple_cmd *cmd, t_token *token);


#endif