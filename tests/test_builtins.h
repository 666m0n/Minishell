#ifndef TEST_BUILTINS_H
# define TEST_BUILTINS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/types.h"

/* Codes couleurs */
# define GREEN   "\033[32m"
# define RED     "\033[31m"
# define RESET   "\033[0m"
# define BG_TEST "\033[48;5;46m"
# define BLACK   "\033[30m"

// Prototypes des fonctions de test
t_ctx *create_test_context(void);
void free_test_context(t_ctx *ctx);
t_command *create_test_command(char **args);
void free_test_command(t_command *cmd);
void capture_output(void);
char *get_captured_output(void);
void print_test_result(const char *test_name, char **cmd_args,
                      const char *expected, const char *got, int result);
void	test_echo_multiple_spaces(void);
void	test_echo_empty_arg(void);
void	test_echo_multiple_empty_args(void);
void	test_echo_mixed_empty_and_text(void);
void	test_echo_n_with_spaces(void);
void	test_echo_tabs(void);
void	test_echo_no_args(void);
void	test_echo_basic(void);
void	test_echo_multiple_args(void);
void	test_echo_n_option(void);
void	test_echo_multiple_n_options(void);
void	test_echo_n_variant(void);
void	test_echo_invalid_option(void);
void	test_echo_only_n(void);


#endif
