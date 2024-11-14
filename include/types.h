/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:51:50 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/14 11:58:44 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/* Forward declarations */
struct	s_ctx;

/* type def pour simplifier prototype fonction create_pipe_array */
typedef int t_pipe[2];

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

/* FDs management */
typedef struct s_fd_state {
    int stdin_backup;
    int stdout_backup;
    int pipe_read;    // Pour heredoc
    int pipe_write;   // Pour heredoc
    int curr_in;      // FD d'entrée actuel
    int curr_out;     // FD de sortie actuel
} t_fd_state;

/* Redirection management */
typedef struct s_redirection
{
	struct s_redirection	*next;	/* Next redirection */
	char					*file;	/* Redirection target */
	t_token					type;	/* Redirection type */
}	t_redirection;

/* Command structure */
typedef struct s_cmd
{
	struct s_cmd		*next;			// Commande suivante dans le pipe
    t_redirection		*redirections;	// Redirections (>, <, >>)
    char				**args;			// Arguments de la commande
    char				*path;			// Chemin de la commande
	t_fd_state			*fd;
	int					exit_status;	// Command exit status
}	t_cmd;

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
