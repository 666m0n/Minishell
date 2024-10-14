/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:21:37 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/14 14:41:44 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parsing.h"
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "\001\033[1;33m\002minishell >$ \001\033[0m\002"

typedef enum e_return
{
	SUCCESS = 0,
	ERROR = -1
}	t_return;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef struct s_env
{
	char			*id;
	char			*value;
	char			*raw;
	struct s_env	*next;
}	t_env;

typedef struct s_ctx
{
	int				def_in;		// FD d'entree par defaut
	int				def_out;
	unsigned char	exit_code;	// code de sortie de la derniere commande
	t_pars_node		*lexer_output;
	t_env			*envp;

}	t_ctx;
#endif