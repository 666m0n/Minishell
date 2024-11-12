/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:51:50 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/11 15:02:18 by emmmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/* Forward declarations */
struct	s_pars_node;
struct	s_ctx;

/* Basic types */
typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_return
{
	RETURN_SUCCESS = 0,
	RETURN_ERROR = -1
}	t_return;

/* Token types */
typedef enum e_token
{
	CMD,			/* Command or simple argument */
	STRING,			/* String literal */
	ESPACE,			/* Space or tab */
	VAR,			/* Environment variable ($...) */
	APPEND,			/* Append redirection (>>) */
	HEREDOC,		/* Here document (<<) */
	REDIR_IN,		/* Input redirection (<) */
	REDIR_OUT,		/* Output redirection (>) */
	D_QUOTE,		/* Double quote (") */
	S_QUOTE,		/* Single quote (') */
	PIPE,			/* Pipe (|) */
	INFILE,			/* Input file */
	OUTFILE			/* Output file */
}	t_token;

/* Environment variables */
typedef struct s_env
{
	struct s_env	*next;		/* Next environment variable */
	char			*raw;		/* Full "name=value" string */
	char			*id;		/* Variable name */
	char			*value;		/* Variable value */
}	t_env;

/* Redirection management */
typedef struct s_redirection
{
	struct s_redirection	*next;	/* Next redirection */
	char					*file;	/* Redirection target */
	t_token					type;	/* Redirection type */
}	t_redirection;

/* Simple command */
typedef struct s_simple_cmd
{
	struct s_simple_cmd  *pipe;          // Commande suivante dans le pipe
    t_redirection       *redirections;   // Redirections (>, <, >>)
    char               **args;           // Arguments de la commande
    char               *path;           // Chemin de la commande
    t_bool             is_builtin;     // Est-ce un builtin?
}	t_simple_cmd;

/* Command structure */
typedef struct s_command
{
	t_simple_cmd	*cmd;			/* Command data */
	int				exit_status;	/* Command exit status */
}	t_command;

/* Shell context */
typedef struct s_ctx
{
	t_env			*envp;			/* Environment variables */
	int				def_in;			/* Default input */
	int				def_out;		/* Default output */
	int				interrupt_flag;	/* Interrupt status */
	unsigned char	exit_code;		/* Last exit code */
}	t_ctx;

#endif
