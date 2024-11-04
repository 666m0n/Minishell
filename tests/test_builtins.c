#include "test_builtins.h"
#include "../include/minishell.h"

/* Variables globales pour la capture de sortie */
static int	stdout_backup;
static int	pipe_fd[2];
static char	output_buffer[4096];

/* Création du contexte de test */
t_ctx	*create_test_context(void)
{
	t_ctx	*ctx;

	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
		return (NULL);
	ctx->def_in = STDIN_FILENO;
	ctx->def_out = STDOUT_FILENO;
	ctx->exit_code = 0;
	ctx->lexer_output = NULL;
	ctx->envp = NULL;
	return (ctx);
}

/* Libération du contexte de test */
void	free_test_context(t_ctx *ctx)
{
	if (!ctx)
		return ;
	free(ctx);
}

/* Création d'une commande de test */
t_command	*create_test_command(char **args)
{
	t_command	*cmd;
	t_simple_cmd	*simple_cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	simple_cmd = malloc(sizeof(t_simple_cmd));
	if (!simple_cmd)
	{
		free(cmd);
		return (NULL);
	}
	simple_cmd->args = args;
	simple_cmd->path = NULL;
	simple_cmd->redirections = NULL;
	simple_cmd->pipe = NULL;
	cmd->cmd = simple_cmd;
	cmd->exit_status = 0;
	return (cmd);
}

/* Libération d'une commande de test */
void	free_test_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd)
		free(cmd->cmd);
	free(cmd);
}

/* Capture de la sortie standard */
void	capture_output(void)
{
	ft_memset(output_buffer, 0, sizeof(output_buffer));
	stdout_backup = dup(STDOUT_FILENO);
	pipe(pipe_fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
}

/* Récupération de la sortie capturée */
char	*get_captured_output(void)
{
	int	bytes_read;

	fflush(stdout);
	close(pipe_fd[1]);
	bytes_read = read(pipe_fd[0], output_buffer, sizeof(output_buffer) - 1);
	if (bytes_read > 0)
		output_buffer[bytes_read] = '\0';
	else
		output_buffer[0] = '\0';
	dup2(stdout_backup, STDOUT_FILENO);
	close(pipe_fd[0]);
	close(stdout_backup);
	return (output_buffer);
}

/* Affichage des résultats de test */
void	print_test_result(const char *test_name, char **cmd_args, const char *expected, const char *got, int result)
{
	t_bool	success;
	int		i;

	success = (strcmp(expected, got) == 0);
	printf("\n");
	printf("\033[48;5;46m\033[30m %s : \033[0m\n\n", test_name);
	printf("Command  : ");
	i = 0;
	while (cmd_args[i])
	{
		printf("%s", cmd_args[i]);
		if (cmd_args[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
	printf("Expected : ");
	i = 0;
	while (expected[i])
	{
		if (expected[i] == '\n')
			printf("$");
		else
			printf("%c", expected[i]);
		i++;
	}
	printf("\n");
	printf("Got      : ");
	i = 0;
	while (got[i])
	{
		if (got[i] == '\n')
			printf("$");
		else
			printf("%c", got[i]);
		i++;
	}
	printf("\n");
	printf("Return   : %d\n", result);
	printf("Status   : %s%s%s\n",
		success ? GREEN : RED,
		success ? "SUCCESS" : "FAILURE",
		RESET);
}
