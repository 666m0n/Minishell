/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:55:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/06 13:50:34 by sviallon         ###   ########.fr       */
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

int				handle_quotes(char *s);



//parser

t_simple_cmd	*new_simple_cmd(void);
void			free_simple_cmd(t_simple_cmd *cmd);
void			free_command(t_command *cmd);
int				handle_argument(t_simple_cmd *cmd, t_pars_node *token);
t_command		*parser(t_pars_node *tokens);
t_redirection	*new_redirection(t_token type, char *file);
void			free_redirection(t_redirection *redir);
void			add_redirection(t_simple_cmd *cmd, t_redirection *new_redir);
int				is_redirection(t_token type);
int				handle_redirection(t_simple_cmd *cmd, t_pars_node *token);
char			*get_env_value(t_env *env, const char *var_name);
size_t			calculate_expanded_length(const char *str,
					t_env *env, int exit_status);
char			*expand_variables(const char *str, t_env *env, int exit_status);
int				expand_token_variables(t_pars_node *token, t_ctx *ctx);
int				expand_all_variables(t_pars_node *tokens, t_ctx *ctx);

#endif