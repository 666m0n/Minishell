/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:55:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/23 11:34:06 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define QUOTE_ERROR "syntax error : missing quote\n"

typedef struct s_ctx	t_ctx;

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

t_pars_node	*lexer_create(char *str, t_ctx *ctx);
t_pars_node	*lexer_last_node(t_pars_node *token);
t_pars_node	*lexer_new_token(char *content, int n, t_token type, t_ctx *ctx);
void		lexer_init_node(t_pars_node *new_node, t_token type, char *content,
				int n);
t_pars_node	*lexer(char *line, t_ctx *ctx);
int			quote_len(char *str, char quote);
int			get_str_len(char *str);
int			lex_get_len(char *str, t_token type);
t_token		lex_get_type(char *str);
char		*ft_strndup(const char *s, size_t n);
int			tok_add_back(t_pars_node **head, t_pars_node *new);
void		free_one_token(t_pars_node	*token);
void		free_token(t_pars_node *token);


#endif