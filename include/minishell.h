/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:21:37 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/30 18:58:02 by emmmarti         ###   ########.fr       */
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

# define SUCCESS 0
# define ERROR 1
# define MISUSE 2
# define CANT_EXECUTE 126
# define IS_DIR 126
# define PERMISSION_DENIED 126
# define CMD_NOT_FOUND 127
# define EXIT_CTRL_C 130
# define EXIT_CTRL_BS 131
# define EXIT_RANGE_ERR 255

int			main(int ac, char **av, char **envp);
int			check_line(char *line);
void		free_all(t_ctx	*ctx);
t_ctx		*init_ctx(char **envp);
t_env		*create_env_list(char **envp);
void		env_del_one(t_env *env);
void		env_free(t_env *env);
t_return	handle_loop(t_ctx *ctx);
void		free_all(t_ctx *ctx);
char		*ft_chartostr(char c);
char		*ft_strjoin_free(char *s1, char *s2);

//builtins
int			execute_builtin(t_simple_cmd *cmd, t_ctx *ctx);
int			is_builtin(char *cmd);
int			bui_env(t_ctx *ctx, t_simple_cmd *cmd);

//external commands
int			execute_external_command(t_command *cmd, char **env);

//main
int			execute_command(t_command *cmd, t_ctx *envp);

//path utils
char		*search_in_directory(char **directories, const char *cmd);
char		*find_command_path(const char *cmd);
t_bool		is_dir(const char *path);
int			check_command(t_command *cmd, char **env);

//test

void		print_tokens(t_pars_node *tokens);
void		print_command(t_command *cmd);

#endif