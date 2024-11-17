/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:45:18 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/16 23:05:52 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>
# include "libft.h"
# include "types.h"
# include "parsing.h"
# include "errors.h"
# include <dirent.h>

/* Constants A VERIFIER L'UTILITE DE PATH PATH DEFAUT */
# define PROMPT "\001\033[1;33m\002minishell >$ \001\033[0m\002"
# define DEFAULT_PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

/* Masque pour isoler les 8 bits de poids fort du statut */
/* 0xff00 = 1111 1111 0000 0000 en binaire */
# define EXIT_CODE_MASK   0xff00

/* Nombre de bits à décaler pour obtenir le code de sortie */
# define EXIT_CODE_SHIFT  8

/* Core Functions */
int				execute_command(t_cmd *cmd, t_ctx *ctx);

/* Command Execution */
int				exec_simple(t_cmd *cmd, t_ctx *ctx);
int				exec_pipe(t_cmd *cmd, t_ctx *ctx);
int				exec_builtin(t_cmd *cmd, t_ctx *ctx);
void			exec_in_child(t_cmd *cmd, t_ctx *ctx);
int				prepare_exec(t_cmd *cmd);

/* Built-in Commands */
int				builtin_echo(t_cmd *cmd, t_ctx *ctx);
int				builtin_cd(t_cmd *cmd, t_ctx *ctx);
int				builtin_pwd(t_cmd *cmd, t_ctx *ctx);
int				builtin_export(t_cmd *cmd, t_ctx *ctx);
int				builtin_unset(t_cmd *cmd, t_ctx *ctx);
int				builtin_env(t_cmd *cmd, t_ctx *ctx);
int				builtin_exit(t_cmd *cmd, t_ctx *ctx);

/* Path Management */
char			*find_command_path(const char *cmd_name);
char			*search_in_directory(char **directories, const char *cmd_name);

/* Pipeline Management */
int				count_pipes(t_cmd *cmd);
t_pipe			*create_pipe_array(int nb_of_pipes);
void			configure_pipe_fds(t_pipe *pipe_array, int cmd_position, int nb_of_pipes);
void			cleanup_remaining_pipes(t_pipe *pipe_array, int nb_of_pipes);
void			close_unused_pipes(t_pipe *pipe_array, int cmd_position, int nb_of_pipes);
int				wait_for_processes(pid_t *pids, int count);

/* Redirection Management */
int				setup_redirections(t_cmd *cmd);
int				restore_fds(t_cmd *cmd);
void			cleanup_fds(t_cmd *cmd);
int				apply_input_redirection(t_cmd *cmd);
int				apply_output_redirection(t_cmd *cmd);

/* Environment Management */
t_env			*find_min_var(t_env *env, char *min_id);
t_env			*find_existing_var(t_env *env, const char *name);
t_env			*create_env_var(const char *name, const char *value);
int				update_existing_var(t_env *var, const char *name, const char *value);
int				extract_name_value(const char *arg, char **name, char **value);

/* Error Handling */
int				handle_command_error(t_cmd *cmd, int error_code);
int				handle_builtin_error(const char *builtin, const char *arg, const char *msg);
int				handle_system_error(const char *syscall);

/* Getters */
const char		*get_cmd_name(t_cmd *cmd);
t_redirection	*get_redirections(t_cmd *cmd);
int				get_exit_status(t_cmd *cmd);
char			*get_cmd_path(t_cmd *cmd);
builtin_func	get_builtin_function(const char *cmd_name);

/* Setters */
void			set_exit_status(t_cmd *cmd, int status);
int				set_cmd_path(t_cmd *cmd, char *path);

/* Utility Functions */
t_bool			is_path(const char *cmd_name);
t_bool			is_dir(const char *path);
t_bool			is_builtin(const char *cmd_name);
t_bool			is_simple_command(t_cmd *cmd);
t_bool			has_redirection(t_cmd *cmd);
void			ft_free_array(char **array);
void			env_del_one(t_env *env);

#endif
