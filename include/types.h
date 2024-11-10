/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:51:50 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/10 10:07:30 by emmanuel         ###   ########.fr       */
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

/* File descriptor management */
typedef struct s_fd_set
{
	int	original;		/* Original file descriptor */
	int	current;		/* Current after redirection/pipe */
	int	backup;			/* Backup for builtin restore */
}	t_fd_set;

/* Heredoc management */
typedef struct s_heredoc
{
	struct s_heredoc	*next;			/* Next heredoc in chain */
	char				*delimiter;		/* Heredoc end keyword */
	char				*content;		/* Stored content */
	int					pipe_fd[2];		/* Read/write pipe ends */
	t_bool				expand_vars;	/* Enable variable expansion */
}	t_heredoc;

/* Process tracking */
typedef struct s_process
{
	struct s_process	*next;		/* Next process in pipeline */
	pid_t				pid;		/* Process identifier */
	int					pipe_in;	/* Input file descriptor */
	int					pipe_out;	/* Output file descriptor */
	int					status;		/* Exit status */
	t_bool				completed;	/* Process completion status */
}	t_process;

/* Pipeline management */
typedef struct s_pipeline
{
	t_process			*processes;	/* List of processes */
	t_heredoc			*heredocs;	/* List of heredocs */
	int					*pipe_fds;	/* Array of pipe descriptors */
	int					proc_count;	/* Number of processes */
	int					pipe_count;	/* Number of pipes */
	t_bool				in_heredoc;	/* Currently reading heredoc */
}	t_pipeline;

/* Environment variables */
typedef struct s_env
{
	struct s_env	*next;		/* Next environment variable */
	char			*raw;		/* Full "name=value" string */
	char			*id;		/* Variable name */
	char			*value;		/* Variable value */
}	t_env;

/* Parser nodes */
typedef struct s_pars_node
{
	struct s_pars_node	*next;		/* Next token */
	struct s_ctx		*ctx;		/* Global shell context */
	char				*content;	/* Token content */
	t_token				type;		/* Token type */
}	t_pars_node;

/* Parser list */
typedef struct s_pars_list
{
	t_pars_node	*start;			/* First token in list */
	t_pars_node	*end;			/* Last token in list */
	int			length;			/* Number of tokens */
}	t_pars_list;

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
	struct s_simple_cmd		*pipe;			/* Next piped command */
	t_redirection			*redirections;	/* Command redirections */
	char					**args;			/* Command arguments */
	char					*path;			/* Command path */
	t_fd_set				input;			/* Input handling */
	t_fd_set				output;			/* Output handling */
	t_bool					is_builtin;		/* Builtin command flag */
}	t_simple_cmd;

/* Command structure */
typedef struct s_command
{
	t_simple_cmd	*cmd;			/* Command data */
	t_pipeline		*pipeline;		/* Pipeline data */
	int				exit_status;	/* Command exit status */
}	t_command;

/* Shell context */
typedef struct s_ctx
{
	t_pars_node		*lexer_output;	/* Lexer results */
	t_env			*envp;			/* Environment variables */
	t_pipeline		*curr_pipeline;	/* Active pipeline */
	t_heredoc		*pend_heredocs;	/* Pending heredocs */
	int				def_in;			/* Default input */
	int				def_out;		/* Default output */
	int				interrupt_flag;	/* Interrupt status */
	unsigned char	exit_code;		/* Last exit code */
}	t_ctx;

#endif
