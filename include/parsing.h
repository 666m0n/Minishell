/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:55:46 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/11 13:28:39 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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