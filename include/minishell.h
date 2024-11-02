/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:45:18 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/02 18:07:00 by emmanuel         ###   ########.fr       */
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
# include "errors.h"
# include <errno.h>
# include <unistd.h>

/* Constants */
# define PROMPT "\001\033[1;33m\002minishell >$ \001\033[0m\002"
# define DEFAULT_PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

/* Type definitions */
typedef int (*builtin_func)(t_command *, t_ctx *);

/* Core Functions */
int				main(int ac, char **av, char **envp);
t_return		handle_loop(t_ctx *ctx);
int				check_line(char *line);

/* Context Management */
t_ctx			*init_ctx(char **envp);
void			free_all(t_ctx *ctx);

/* Environment Management */
t_env			*create_env_list(char **envp);
void			env_del_one(t_env *env);
void			env_free(t_env *env);

/* Command Execution */
int				execute_command(t_command *cmd, t_ctx *ctx);
int				execute_external_command(t_command *cmd, char **env);
int				execute_builtin(t_command *cmd, t_ctx *ctx);
t_bool			is_builtin(char *cmd);

/* Built-in Commands */
int				builtin_echo(t_command *cmd, t_ctx *ctx);
int				builtin_cd(t_command *cmd, t_ctx *ctx);
int				builtin_pwd(t_command *cmd, t_ctx *ctx);
int				builtin_env(t_command *cmd, t_ctx *ctx);
int				builtin_exit(t_command *cmd, t_ctx *ctx);
int				builtin_export(t_command *cmd, t_ctx *ctx);
int				builtin_unset(t_command *cmd, t_ctx *ctx);

/* Path Management */
char			*find_command_path(const char *cmd);
t_bool			is_dir(const char *path);
int				check_command(t_command *cmd);

/* Getters */
const char		*get_command_name(t_command *cmd);
int				get_exit_status(t_command *cmd);
char			*get_command_path(t_command *cmd);
builtin_func	get_builtin_function(const char *cmd_name);

/* Setters */
void			set_exit_status(t_command *cmd, int status);
int				set_command_path(t_command *cmd, char *path);

/* Utility Functions */
void			ft_free_array(char **array);
char			*ft_chartostr(char c);
char			*ft_strjoin_free(char *s1, char *s2);

#endif
