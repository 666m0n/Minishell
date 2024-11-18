/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:58:45 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/10 11:37:45 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/* Valeurs de retour système standards */
# define SYSCALL_ERROR			-1		// Valeur de retour d'erreur standard des appels système
# define SYSCALL_SUCCESS		0

/* Guide des codes d'erreur principaux */
// Succès
# define SUCCESS				0		// La commande s'est exécutée avec succès

// Erreurs générales (1-2)
# define ERROR					1		// Erreur générale (ex: cd vers un dossier inexistant)
# define MISUSE					2		// Mauvaise utilisation (ex: export sans argument)

// Erreurs spécifiques à minishell (3-125)
# define FORK_ERROR				3		// Erreur lors du fork
# define PIPE_ERROR				4		// Erreur lors de la création d'un pipe
# define MEMORY_ERROR			5		// Erreur d'allocation mémoire
# define SYNTAX_ERROR			6		// Erreur de syntaxe dans la commande
# define INTERRUPT				7		// Interruption (Ctrl-C/Ctrl-D)

// Erreurs d'exécution (126-127)
# define PERMISSION_DENIED		126		// Fichier existe mais pas les droits
# define IS_DIR					126		// Tentative d'exécuter un dossier
# define CANT_EXECUTE			126		// Fichier non exécutable
# define CMD_NOT_FOUND			127		// Commande introuvable

// Erreurs de signal (128+)
# define EXIT_CTRL_C			130		// Interruption par Ctrl+C (128 + SIGINT)
# define EXIT_CTRL_BS			131		// Quit par Ctrl+\ (128 + SIGQUIT)

// Macros utiles pour les signaux
# define EXIT_BY_SIGNAL(sig) (128 + sig)  // Calcule le code de sortie pour un signal

// Macros de vérification
# define IS_ERROR(code)     ((code) != SUCCESS)
# define IS_FATAL(code)     ((code) == MEMORY_ERROR || (code) == FORK_ERROR)

#endif
