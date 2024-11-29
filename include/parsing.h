/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Simon <Simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:55:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/27 15:51:55 by Simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types.h"

# define QUOTE_ERROR "syntax error : missing quote\n"
# define IS_TOKEN "\"'|<>&"
# define IS_REDIRECTION "<>"

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
void		skip_consecutive_quotes(char **str, char *quote_type,
				int *effective_q);
t_token		get_quote_type(char quote);
char		*get_quote_content(char **str, char quote, char changed);
t_return	syntax_tokens(t_lexer *tokens, t_ctx *data);
t_syntax	*create_syntax_list(t_lexer *tokens);
void		free_syntax_list(t_syntax *list);
int			is_directory(const char *content);
int			handle_misc(t_syntax *token);
void		change_exit_code(int status, t_ctx *data);


//parser
t_cmd		*parser(t_lexer *tokens, t_ctx *data);
void		free_cmd(t_cmd *cmd);
int			is_redir(t_token type);
int			is_cmd(t_token type);
void		extend_cmd(t_cmd **cmd, t_ctx *data);
void		handle_redir(t_cmd *cmd, t_lexer **tokens);
void		process_pars(t_cmd *cmd, t_lexer *tokens, t_ctx *data);
size_t		get_var_len(char *s, size_t *i);


//dollar expansion
void		handle_dollar(t_lexer *token, t_ctx *data);
char		*replace_var(char *s, t_ctx *data, size_t *i);
char		*get_env_value(t_env *env, char *var_name);

//test
int			execute_builtin(t_ctx *ctx, t_cmd *cmd);
int			bui_env(t_ctx *ctx, t_cmd *cmd);
void		env_free(t_env *env);
void		env_del_one(t_env *env);
t_env		*create_env_list(char **envp);

#endif