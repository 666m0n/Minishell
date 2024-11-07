/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:55:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/07 11:42:58 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types.h"

# define QUOTE_ERROR "syntax error : missing quote\n"

typedef enum e_token_type
{
	T_STRING,
	T_PIPE,
	T_INPUT,
	T_OUTPUT,
	T_APPEND,
	T_HEREDOC,
	T_SQUOTE,
	T_DQUOTE,
	T_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	int				expandable;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_lexer
{
	char		*input;
	size_t		pos;
	size_t		len;
	t_token		*head;
	t_token		*current;
	int			last_exit;
	t_env		*env;
}	t_lexer;

typedef struct s_redirection
{
	t_token_type			type;
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

int				handle_quotes(char *s);
int				get_close_quote(char *s, char c);
int				get_token_str_len(char *s);
int				get_token_len(char *s, t_token_type type);
t_token_type	get_token_type(char *s);
t_token			*tokenize(char *s);
int				add_str_len(char *s, t_token_type type);
void			init_lexer(t_lexer *lexer, char *input,
					t_env *env, int last_exit);
t_token			*lexer(char *input, t_env *env, int last_exit);
void			free_token(t_token *tok);
char			*copy_str(const char *src,
					char *to_ret, int len, t_token_type type);
t_token			*create_token(const char *s, int len, t_token_type type);
void			add_token(t_lexer *lexer, t_token *new_node);
char			*ft_strndup(const char *s, size_t n);

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
char			*get_env_value(t_env *env, const char *var_name);
size_t			calculate_expanded_length(const char *str,
					t_env *env, int exit_status);
char			*expand_variables(const char *str, t_env *env, int exit_status);
int				handle_string_token(t_simple_cmd *cmd, t_token *token);

#endif