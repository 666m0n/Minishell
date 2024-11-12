/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:55:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/12 13:27:38 by sviallon         ###   ########.fr       */
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



//parser



#endif