/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:51:50 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/07 10:47:17 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

struct	s_pars_node;
struct	s_env;
struct	s_ctx;

typedef struct s_env
{
	char			*id;
	char			*value;
	char			*raw;
	struct s_env	*next;
}	t_env;

typedef struct s_ctx
{
	int						def_in;		// FD d'entree par defaut
	int						def_out;
	unsigned char			exit_code;	// code de sortie de la derniere commande
	struct s_pars_node		*lexer_output;
	t_env			*envp;
}	t_ctx;

#endif