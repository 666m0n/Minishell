/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:55:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/30 17:10:23 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types.h"

# define QUOTE_ERROR "syntax error : missing quote\n"

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
	REDIR_IN, // mettre le nom de ficher dedans directemet (voir avec Manu)
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
	t_redirection		*redirections;
	struct s_simple_cmd	*pipe;
}	t_simple_cmd;

typedef struct s_command
{
	t_simple_cmd	*cmd; // premiere cmd
	int				exit_status; // pour gerer $?
}	t_command;

t_pars_node		*lexer_create(char *str, t_ctx *ctx);
t_pars_node		*lex_last_tok(t_pars_node *token);
t_pars_node		*lexer_new_token(char *content, int n, t_token type,
					t_ctx *ctx);
void			lexer_init_node(t_pars_node *new_node, t_token type,
					char *content, int n);
t_pars_node		*lexer(char *line, t_ctx *ctx);
int				quote_len(char *str, char quote);
int				get_str_len(char *str);
int				lex_get_len(char *str, t_token type);
t_token			lex_get_type(char *str);
char			*ft_strndup(const char *s, size_t n);
int				tok_add_back(t_pars_node **head, t_pars_node *new);
void			free_one_token(t_pars_node	*token);
void			free_token(t_pars_node *token);
int				handle_quotes(char *s);
int				is_in_squote(const char *str, int pos);
int				process_token_content(t_pars_node *token, t_ctx *ctx,
					t_token type);
int				process_quotes(t_pars_node *tokens, t_ctx *ctx, t_token type);
char			*expand_token(char *str, t_ctx *ctx, t_token type);

//parser

t_simple_cmd	*new_simple_cmd(void);
void			free_simple_cmd(t_simple_cmd *cmd);
void			free_command(t_command *cmd);
int				parser_handler(t_pars_node **token);
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