/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:21:37 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/11 13:55:40 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parsing.h"
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "\001\033[1;33m\002minishell >$ \001\033[0m\002"

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef struct s_env
{
	char			*id;	// Nom de la variable d'env
	char			*value;	// valeur de la variable
	char			*raw;	// Representation brute "nom=valeur"
	struct s_env	*next;
}	t_env

#endif