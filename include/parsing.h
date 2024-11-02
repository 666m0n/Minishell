/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:55:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/02 18:19:28 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types.h"

/* Messages d'erreur */
# define QUOTE_ERROR "syntax error : missing quote\n"

/* Fonctions du lexer */
t_pars_node     *lexer(char *line, t_ctx *ctx);
t_pars_node     *lexer_create(char *str, t_ctx *ctx);
t_pars_node     *lex_last_tok(t_pars_node *token);
t_pars_node     *lexer_new_token(char *content, int n, t_token type, t_ctx *ctx);
void            lexer_init_node(t_pars_node *new_node, t_token type, char *content, int n);

/* Fonctions utilitaires du lexer */
int             quote_len(char *str, char quote);
int             get_str_len(char *str);
int             lex_get_len(char *str, t_token type);
t_token         lex_get_type(char *str);
char            *ft_strndup(const char *s, size_t n);
int             tok_add_back(t_pars_node **head, t_pars_node *new);

/* Gestion des tokens */
void            free_one_token(t_pars_node *token);
void            free_token(t_pars_node *token);

/* Gestion des quotes */
int             handle_quotes(char *s);
int             close_quote_len(char *s, char c);

/* Traitement des tokens */
int             process_token_content(t_pars_node *token, t_ctx *ctx);
int             process_quotes(t_pars_node *tokens, t_ctx *ctx);
char            *process_token(char *str);
void            copy_token_content(char *dest, char *src);
char            *expand_token(char *str, t_ctx *ctx);

/* Fonctions du parser */
t_command       *parser(t_pars_node *tokens);
t_simple_cmd    *new_simple_cmd(void);
int             parser_handler(t_pars_node **token);
int             handle_argument(t_simple_cmd *cmd, t_pars_node *token);

/* Gestion des redirections */
t_redirection   *new_redirection(t_token type, char *file);
void            add_redirection(t_simple_cmd *cmd, t_redirection *new_redir);
int             is_redirection(t_token type);
int             handle_redirection(t_simple_cmd *cmd, t_pars_node *token);

/* Gestion de la mémoire */
void            free_simple_cmd(t_simple_cmd *cmd);
void            free_command(t_command *cmd);
void            free_redirection(t_redirection *redir);

/* Gestion des variables d'environnement */
char            *get_env_value(t_env *env, const char *var_name);
size_t          calculate_expanded_length(const char *str, t_env *env, int exit_status);
char            *expand_variables(const char *str, t_env *env, int exit_status);
int             expand_token_variables(t_pars_node *token, t_ctx *ctx);
int             expand_all_variables(t_pars_node *tokens, t_ctx *ctx);

#endif
