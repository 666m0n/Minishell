/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:55:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/15 19:36:05 by sviallon         ###   ########.fr       */
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

typedef struct s_cmd
{
	char				**args;
	t_redirection		*redirections;
	struct s_cmd		*next;
	struct s_cmd		*prev;
	char				*path;
	int					index;
	int					stdin_backup;
	int					stdout_backup;
}	t_cmd;

//lexer
t_lexer		*lexer(char *input);
void		add_index_token(t_lexer *tokens);
void		free_token(t_lexer *tokens);
void		create_token(t_token type, char *content, t_lexer **tokens);
t_lexer		*lst_getlast(t_lexer *node);
void		init_token(t_lexer *new_token, t_token type, char *content);
int			ft_isspace(char c);
void		handle_less(t_lexer **token, char **str, char *new);
void		handle_greater(t_lexer **token, char **str, char *new);
void		redir_handler(t_lexer **token, char **str);
void		pipe_handler(t_lexer **tokens, char **str);
void		space_handler(t_lexer **tokens, char **str);
void		quotes_handler(t_lexer **tokens, char **str);

//parser
t_cmd		*parser(t_lexer *tokens, t_ctx *data);
void		free_cmd(t_cmd *cmd);
int			is_redir(t_token type);
int			is_cmd(t_token type);
void		extend_cmd(t_cmd **cmd, t_ctx *data);
void		handle_redir(t_cmd *cmd, t_lexer **tokens);
void		process_pars(t_cmd *cmd, t_lexer *tokens, t_ctx *data);

//dollar expansion
void		handle_dollar(t_lexer *token, t_ctx *data);
char		*replace_var(char *s, t_ctx *data, int *i);
char		*replace_dollar(char *s, t_ctx *data);

#endif