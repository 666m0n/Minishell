/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:21:37 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/11 11:23:17 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "\001\033[1;33m\002minishell >$ \001\033[0m\002"

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_token
{
	CMD,
	STRING,
	ESPACE,
	VAR,
	REDIR_IN,
	REDIR_OUT,
	D_QUOTE,
	S_QUOTE,
	PIPE
}	t_token;

typedef struct s_pars_node
{
	t_token				type;
	char				*content;
	struct s_pars_node	*next;
	struct s_pars_node	*prev;
	int					index;
}	t_pars_node;

typedef struct s_pars_list
{
	t_pars_node	*start;
	t_pars_node	*end;
	int			length;
}	t_pars_list;


#endif