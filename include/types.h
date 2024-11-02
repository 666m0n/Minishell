/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:51:50 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/02 18:14:17 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/* Forward declarations pour éviter les dépendances circulaires */
struct s_pars_node;
struct s_ctx;

/* Types basiques */
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

/* Types pour le lexer/parser */
typedef enum e_token
{
	CMD,     // Mot simple (commande ou argument)
	STRING,   // Chaîne de caractères
	ESPACE,    // Espace ou tabulation
	VAR,      // Variable ($...)
	APPEND,   // Redirection en mode append (>>)
	HEREDOC,  // Here document (<<)
	REDIR_IN, // Redirection entrée (<)
	REDIR_OUT,// Redirection sortie (>)
	D_QUOTE,  // Double quote (")
	S_QUOTE,  // Single quote (')
	PIPE,     // Pipe (|)
	INFILE,
	OUTFILE
}	t_token;

/* Structures pour la gestion de l'environnement */
typedef struct s_env
{
	char			*id;    // Nom de la variable
	char			*value; // Valeur de la variable
	char			*raw;   // Chaîne brute "id=value"
	struct s_env	*next;
}	t_env;

/* Structures pour le parsing */
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

/* Structures pour les commandes */
typedef struct	s_redirection
{
	t_token					type;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_simple_cmd
{
	t_redirection		*redirections;
	struct s_simple_cmd	*pipe;
	char				**args;
	char				*path;
}	t_simple_cmd;

typedef struct s_command
{
	t_simple_cmd	*cmd;
	int				exit_status;
}	t_command;

/* Structure de contexte global */
typedef struct s_ctx
{
	int				def_in;         // FD d'entrée par défaut
	int				def_out;        // FD de sortie par défaut
	unsigned char	exit_code;      // Code de sortie de la dernière commande
	t_pars_node		*lexer_output;  // Sortie du lexer
	t_env			*envp;          // Variables d'environnement
}	t_ctx;

#endif
