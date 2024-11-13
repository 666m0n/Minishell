/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:45:18 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/13 15:56:46 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <unistd.h>
#include <stddef.h>
#include <fcntl.h>
# include "libft.h"
# include "types.h"
# include "parsing.h"
# include "errors.h"
# include <dirent.h>


/* Constants */
# define PROMPT "\001\033[1;33m\002minishell >$ \001\033[0m\002"
# define DEFAULT_PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

/* Process status masks and shifts */

/* Masque pour isoler les 8 bits de poids fort du statut */
/* 0xff00 = 1111 1111 0000 0000 en binaire */
# define EXIT_CODE_MASK   0xff00

/* Nombre de bits à décaler pour obtenir le code de sortie */
# define EXIT_CODE_SHIFT  8

/* Type definitions */
typedef int (*builtin_func)(t_cmd *, t_ctx *);

/* Core Functions */
int				main(int ac, char **av, char **envp);
t_return		handle_loop(t_ctx *ctx);
int				check_line(char *line);

/* Context Management */
t_ctx			*init_ctx(char **envp);
void			free_all(t_ctx *ctx);

/* Process Management */
pid_t			create_child_process(void);
void			exec_in_child(t_cmd *cmd, t_ctx *ctx);
int				wait_child(pid_t pid);

/* Environment Management */
t_env			*create_env_list(char **envp);
void			env_del_one(t_env *env);
void			env_free(t_env *env);

/* Command Execution */
int				execute_command(t_cmd *cmd, t_ctx *ctx);
int				execute_external_command(t_cmd *cmd, t_ctx *ctx);
int				execute_builtin(t_cmd *cmd, t_ctx *ctx);
t_bool			is_builtin(const char *cmd);

/* Built-in Commands */
int				builtin_echo(t_cmd *cmd, t_ctx *ctx);
int				builtin_cd(t_cmd *cmd, t_ctx *ctx);
int				builtin_pwd(t_cmd *cmd, t_ctx *ctx);
int				builtin_env(t_cmd *cmd, t_ctx *ctx);
int				builtin_exit(t_cmd *cmd, t_ctx *ctx);
int				builtin_export(t_cmd *cmd, t_ctx *ctx);
int				builtin_unset(t_cmd *cmd, t_ctx *ctx);

/* Path Management */
char			*find_command_path(const char *cmd);
t_bool			is_dir(const char *path);
int				check_command(t_cmd *cmd);

/* Getters */
const char		*get_cmd_name(t_cmd *cmd);
int				get_exit_status(t_cmd *cmd);
char			*get_cmd_path(t_cmd *cmd);
builtin_func	get_builtin_function(const char *cmd_name);

/* Setters */
void			set_exit_status(t_cmd *cmd, int status);
int				set_cmd_path(t_cmd *cmd, char *path);

/* Utility Functions */
void			ft_free_array(char **array);
char			*ft_chartostr(char c);
char			*ft_strjoin_free(char *s1, const char *s2);

/* A trier */
int handle_builtin_error(const char *builtin, const char *arg, const char *msg);
t_env	*find_min_var(t_env *env, char *min_id);
int	extract_name_value(const char *arg, char **name, char **value);
t_bool	is_valid_identifier(const char *var_name);
t_env	*find_existing_var(t_env *env, const char *name);
int update_existing_var(t_env *var, const char *name, const char *value);
t_env	*create_env_var(const char *name, const char *value);
int handle_command_error(t_cmd *cmd, int error_code);
void	ft_free_array(char **array);
int handle_builtin_error(const char *builtin, const char *arg, const char *msg);
int handle_system_error(const char *syscall);
int	ft_str_isdigit(const char *str);
pid_t   create_child_process(void);
int     wait_child(pid_t pid);
void    exec_in_child(t_cmd *cmd, t_ctx *ctx);



#endif
