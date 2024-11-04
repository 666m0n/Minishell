#include "test_builtins.h"
#include "../include/minishell.h"

/* Tests existants... */

void	test_echo_no_args(void)
{
	char	*args[] = {"echo", NULL};
	t_ctx	*ctx = create_test_context();
	t_command *cmd = create_test_command(args);

	capture_output();
	int result = builtin_echo(cmd, ctx);
	char *output = get_captured_output();

	print_test_result("Test echo without args",
					 args,
					 "\n",
					 output,
					 result);

	free_test_command(cmd);
	free_test_context(ctx);
}

void	test_echo_basic(void)
{
	char	*args[] = {"echo", "hello", "world", NULL};
	t_ctx	*ctx = create_test_context();
	t_command *cmd = create_test_command(args);

	capture_output();
	int result = builtin_echo(cmd, ctx);
	char *output = get_captured_output();

	print_test_result("Test echo basic",
					 args,
					 "hello world\n",
					 output,
					 result);

	free_test_command(cmd);
	free_test_context(ctx);
}

void	test_echo_multiple_args(void)
{
	char	*args[] = {"echo", "one", "two", "three", "four", "five", NULL};
	t_ctx	*ctx = create_test_context();
	t_command *cmd = create_test_command(args);

	capture_output();
	int result = builtin_echo(cmd, ctx);
	char *output = get_captured_output();

	print_test_result("Test echo multiple args",
					 args,
					 "one two three four five\n",
					 output,
					 result);

	free_test_command(cmd);
	free_test_context(ctx);
}

void	test_echo_n_option(void)
{
	char	*args[] = {"echo", "-n", "hello", "world", NULL};
	t_ctx	*ctx = create_test_context();
	t_command *cmd = create_test_command(args);

	capture_output();
	int result = builtin_echo(cmd, ctx);
	char *output = get_captured_output();

	print_test_result("Test echo -n option",
					 args,
					 "hello world",
					 output,
					 result);

	free_test_command(cmd);
	free_test_context(ctx);
}

void	test_echo_multiple_n_options(void)
{
	char	*args[] = {"echo", "-n", "-n", "-n", "hello", NULL};
	t_ctx	*ctx = create_test_context();
	t_command *cmd = create_test_command(args);

	capture_output();
	int result = builtin_echo(cmd, ctx);
	char *output = get_captured_output();

	print_test_result("Test echo multiple -n options",
					 args,
					 "hello",
					 output,
					 result);

	free_test_command(cmd);
	free_test_context(ctx);
}

void	test_echo_n_variant(void)
{
	char	*args[] = {"echo", "-nnnnnnn", "hello", NULL};
	t_ctx	*ctx = create_test_context();
	t_command *cmd = create_test_command(args);

	capture_output();
	int result = builtin_echo(cmd, ctx);
	char *output = get_captured_output();

	print_test_result("Test echo -nnnnnnn option",
					 args,
					 "hello",
					 output,
					 result);

	free_test_command(cmd);
	free_test_context(ctx);
}

void	test_echo_invalid_option(void)
{
	char	*args[] = {"echo", "-x", "hello", NULL};
	t_ctx	*ctx = create_test_context();
	t_command *cmd = create_test_command(args);

	capture_output();
	int result = builtin_echo(cmd, ctx);
	char *output = get_captured_output();

	print_test_result("Test echo invalid option",
					 args,
					 "-x hello\n",
					 output,
					 result);

	free_test_command(cmd);
	free_test_context(ctx);
}

void	test_echo_only_n(void)
{
	char	*args[] = {"echo", "-n", NULL};
	t_ctx	*ctx = create_test_context();
	t_command *cmd = create_test_command(args);

	capture_output();
	int result = builtin_echo(cmd, ctx);
	char *output = get_captured_output();

	print_test_result("Test echo only -n",
					 args,
					 "",
					 output,
					 result);

	free_test_command(cmd);
	free_test_context(ctx);
}

void	test_echo_multiple_spaces(void)
{
	char	*args[] = {"echo", "hello", "   ", "world", NULL};
	t_ctx	*ctx = create_test_context();
	t_command *cmd = create_test_command(args);

	capture_output();
	int result = builtin_echo(cmd, ctx);
	char *output = get_captured_output();

	print_test_result("Test echo with multiple spaces",
					 args,
					 "hello     world\n",
					 output,
					 result);

	free_test_command(cmd);
	free_test_context(ctx);
}

void	test_echo_empty_arg(void)
{
	char	*args[] = {"echo", "", NULL};
	t_ctx	*ctx = create_test_context();
	t_command *cmd = create_test_command(args);

	capture_output();
	int result = builtin_echo(cmd, ctx);
	char *output = get_captured_output();

	print_test_result("Test echo empty arg",
					 args,
					 "\n",
					 output,
					 result);

	free_test_command(cmd);
	free_test_context(ctx);
}

void	test_echo_multiple_empty_args(void)
{
	char	*args[] = {"echo", "", "", "", NULL};
	t_ctx	*ctx = create_test_context();
	t_command *cmd = create_test_command(args);

	capture_output();
	int result = builtin_echo(cmd, ctx);
	char *output = get_captured_output();

	print_test_result("Test echo multiple empty args",
					 args,
					 "  \n",
					 output,
					 result);

	free_test_command(cmd);
	free_test_context(ctx);
}

void	test_echo_mixed_empty_and_text(void)
{
	char	*args[] = {"echo", "hello", "", "world", "", "!", NULL};
	t_ctx	*ctx = create_test_context();
	t_command *cmd = create_test_command(args);

	capture_output();
	int result = builtin_echo(cmd, ctx);
	char *output = get_captured_output();

	print_test_result("Test echo mixed empty and text args",
					 args,
					 "hello  world  !\n",
					 output,
					 result);

	free_test_command(cmd);
	free_test_context(ctx);
}

void	test_echo_n_with_spaces(void)
{
	char	*args[] = {"echo", "-n", "", "hello", "   ", "world", NULL};
	t_ctx	*ctx = create_test_context();
	t_command *cmd = create_test_command(args);

	capture_output();
	int result = builtin_echo(cmd, ctx);
	char *output = get_captured_output();

	print_test_result("Test echo -n with spaces",
					 args,
					 " hello     world",
					 output,
					 result);

	free_test_command(cmd);
	free_test_context(ctx);
}

void	test_echo_tabs(void)
{
	char	*args[] = {"echo", "hello\tworld", NULL};
	t_ctx	*ctx = create_test_context();
	t_command *cmd = create_test_command(args);

	capture_output();
	int result = builtin_echo(cmd, ctx);
	char *output = get_captured_output();

	print_test_result("Test echo with tabs",
					 args,
					 "hello\tworld\n",
					 output,
					 result);

	free_test_command(cmd);
	free_test_context(ctx);
}

int test_main(void)
{
	// Tests existants
	test_echo_no_args();
	test_echo_basic();
	test_echo_multiple_args();
	test_echo_n_option();
	test_echo_multiple_n_options();
	test_echo_n_variant();
	test_echo_invalid_option();
	test_echo_only_n();

	// Nouveaux tests
	test_echo_multiple_spaces();
	test_echo_empty_arg();
	test_echo_multiple_empty_args();
	test_echo_mixed_empty_and_text();
	test_echo_n_with_spaces();
	test_echo_tabs();

	return (0);
}
