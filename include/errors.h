/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:58:45 by emmanuel          #+#    #+#             */
/*   Updated: 2024/12/12 19:18:35 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/* Valeurs de retour système standards */
# define SYSCALL_ERROR			-1
# define SYSCALL_SUCCESS		0

// Erreur pour la built in exit
# define INVALID_NUMERIC_ARG -1

/* Guide des codes d'erreur principaux */
// Succès
# define SUCCESS				0

// Erreurs générales (1-2)
# define ERROR					1
# define MISUSE					2

// Erreurs spécifiques à minishell (3-125)
# define FORK_ERROR				3
# define PIPE_ERROR				4
# define MEMORY_ERROR			5
# define SYNTAX_ERROR			6
# define INTERRUPT				7

// Erreurs d'exécution (126-127)
# define PERMISSION_DENIED		126
# define IS_DIR					126
# define CANT_EXECUTE			9
# define CMD_NOT_FOUND			127

// Erreurs de signal (128+)
# define EXIT_CTRL_C			130
# define EXIT_CTRL_BS			131

#endif