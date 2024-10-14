/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:21:37 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/14 15:56:35 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parsing.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

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

int		main(int ac, char **av, char **envp);
int		check_line(char *line);
void	free_all(t_ctx	*ctx);
t_ctx	*init_ctx(char **envp);
t_env	*create_env_list(char **envp);
void	env_del_one(t_env *env);
void	env_free(t_env *env);

#endif