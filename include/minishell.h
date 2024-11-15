/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:21:37 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/15 20:35:05 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "types.h"
# include "parsing.h"

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

// Main functions
int			main(int ac, char **av, char **envp);
void		free_all(t_ctx *ctx);
void		free_double(char **tab);
void		exit_error(const char *s);
int			check_line(char *line);
t_ctx		*init_ctx(char **envp);

// Utils
char		*ft_realloc(void *s, int old_size, int new_size);
char		*ft_strjoin_free(char *s1, char *s2);
size_t		ft_strcpy(char *dest, const char *src);
size_t		ft_strcat(char *dest, char *src);

// Debug functions
void		print_tokens(t_lexer *tokens);
void		print_command(t_cmd *cmd);

#endif