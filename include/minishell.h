/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:21:37 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/18 16:59:12 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <unistd.h>
# include <stddef.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include "types.h"
# include "parsing.h"
# include "errors.h"

# define PROMPT "\001\033[1;33m\002minishell >$ \001\033[0m\002"
# define DEFAULT_PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

/* Masque pour isoler les 8 bits de poids fort du statut */
/* 0xff00 = 1111 1111 0000 0000 en binaire */
# define EXIT_CODE_MASK   0xff00

/* Nombre de bits à décaler pour obtenir le code de sortie */
# define EXIT_CODE_SHIFT  8

//Manu
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
void			configure_pipe_fds(t_pipe *pipe_array, int cmd_position, \
					int nb_of_pipes);
void			cleanup_remaining_pipes(t_pipe *pipe_array, int nb_of_pipes);
void			close_unused_pipes(t_pipe *pipe_array, int cmd_position, \
					int nb_of_pipes);
int				wait_for_processes(pid_t *pids, int count);
int				run_pipeline(t_cmd *cmd, t_pipe *pipe_array, \
					int nb_of_pipes, t_ctx *ctx);
int				init_pipeline(int nb_of_pipes, pid_t **pid_array_ptr);
pid_t			fork_pipeline_process(t_cmd *cmd, t_pipe *pipe_array, \
							int position, int nb_of_pipes, t_ctx *ctx);

/* Redirection Management */
int				setup_redirections(t_cmd *cmd);
int				restore_fds(t_cmd *cmd);
void			cleanup_fds(t_cmd *cmd);
int				apply_input_redirection(t_cmd *cmd);
int				apply_output_redirection(t_cmd *cmd);

/* Environment Management */
t_env			*find_existing_var(t_env *env, const char *name);
int				display_sorted_env(t_ctx *ctx);
void			free_env_var(t_env *var);

/* Error Handling */
int				handle_command_error(t_cmd *cmd, int error_code);
int				handle_builtin_error(const char *builtin, const char *arg, \
					const char *msg);
int				handle_system_error(const char *syscall);
int				handle_syntax_error(const char *token);

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
t_bool			is_valid_command(t_cmd *cmd);
/* void			env_del_one(t_env *env); */

/* a trier */
char			*extract_value(const char *arg);
t_env			*create_var(const char *arg, char *value);
t_env			*update_env_variable(t_ctx *ctx, char *arg);
int				is_valid_identifier(const char *str);
int				setup_heredoc(t_cmd *cmd); // j'ai mis un type au hasard
int				handle_redirections(t_cmd *cmd);
void			find_final_redirections(t_cmd *cmd);
int				save_fd(t_cmd *cmd);


//Simon
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