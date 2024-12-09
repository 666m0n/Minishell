/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:51:50 by sviallon          #+#    #+#             */
/*   Updated: 2024/12/09 17:10:31 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "parsing.h"

//PATOUCHE
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

//PATOUCHE AUSSI
typedef struct s_lexer
{
	struct s_lexer	*next;
	struct s_lexer	*prev;
	char			*content;
	t_token			type;
	int				index;
}	t_lexer;

//modifier la fonction t_return type
typedef enum e_return
{
	SUCCESS = 0,
	ERROR = -1
}	t_return;

/* Basic types */
typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

/* Environment variables */
typedef struct s_env
{
	struct s_env	*next;			/* Next environment variable */
	char			*raw;			/* Full "name=value" string */
	char			*id;			/* Variable name */
	char			*value;			/* Variable value */
}	t_env;

/* Redirection management */
typedef struct s_redirection
{
	struct s_redirection	*next;	/* Next redirection */
	char					*file;	/* Redirection target */
	t_token					type;	/* Redirection type */
}	t_redirection;

/* FDs management */
typedef struct s_fd_state
{
	int	stdin_backup;				/* FD d'entrée par défaut */
	int	stdout_backup;				/* FD de sortie par défaut */
	int	pipe_read;					/* Pour heredoc */
	int	pipe_write;					/* Pour heredoc */
	int	curr_in;					/* FD d'entrée actuel */
	int	curr_out;					/* FD de sortie actuel */
    t_redirection   *last_in;       // Pour garder la dernière redirection d'entrée
    t_redirection   *last_out;      // Pour garder la dernière redirection de sortie
}	t_fd_state;

/* Command structure */
typedef struct s_cmd
{
    struct s_ctx    *ctx; 
	struct s_cmd	*prev;
	struct s_cmd	*next;			/* Commande suivante dans le pipe */
	t_redirection	*redirections;	/* Redirections (>, <, >>) */
	char			**args;			/* Arguments de la commande */
	char			*path;			/* Chemin de la commande */
	t_fd_state		*fd;
	int				index;
	int				exit_status;	/* Command exit status */
}	t_cmd;

/* Shell context */
typedef struct s_ctx
{
	t_env			*envp;			/* Environment variables */
	int				def_in;			/* Default input */
	int				def_out;		/* Default output */
	int				interrupt_flag;	/* Interrupt status pas utile encore ?*/
	unsigned char	exit_code;		/* Last exit code */
	t_lexer			*current_token;
}	t_ctx;

typedef struct s_syntax
{
	struct s_syntax	*next;
	struct s_syntax	*prev;
	char			*content;
	t_token			type;
	int				index;
}	t_syntax;

/*gestion des retours
typedef struct s_minishell
{
	char	*line;
	int		i;
}	t_minishell; */

#endif