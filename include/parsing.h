/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:55:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/14 14:34:07 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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
	struct s_pars_node	*prev;
	int					index;
}	t_pars_node;

typedef struct s_pars_list
{
	t_pars_node	*start;
	t_pars_node	*end;
	int			length;
}	t_pars_list;


t_pars_node	*lexer_create(char *str, t_ctx *ctx, t_pars_node **token);
void		lexer(char *line, t_ctx *ctx);
t_pars_node	*lexer_last_node(t_pars_node *token);
t_pars_node	*lexer_new_node(t_token type, char *content, int len,
				t_pars_node **token);
void		lexer_init_node(t_pars_node *new_node, t_token type, char *content);
int			quote_len(char *str, char quote);
int			get_str_len(char *str);
int			lex_get_len(char *str, t_token type);
t_token		ex_get_type(char *str);

#endif