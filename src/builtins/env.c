/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:09:29 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/03 18:38:57 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// pour stocker les var d'env dans une liste chainee
t_env	*create_env_list(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	char	*equals;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		new_node->raw = ft_strdup(envp[i]);
		equals = strchr(new_node->raw, '=');
		if (equals)
		{
			*equals = '\0';
			new_node->id = new_node->raw;
			new_node->value = equals + 1;
		}
		new_node->next = env_list;
		env_list = new_node;
		i++;
	}
	return (env_list);
}

void	env_del_one(t_env *env)
{
	if (env)
	{
		if (env->raw)
			free(env->raw);
		free(env);
	}
}

//clean la liste chainee des var d'env
void	env_free(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		env_del_one(tmp);
	}
}

static void	bui_err_env(char *arg)
{
	ft_putstr_fd("env: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
}

int	bui_env(t_ctx *ctx, t_simple_cmd *cmd)
{
	t_env	*tmp;

	if (cmd->args && cmd->args[1])
	{
		bui_err_env(cmd->args[1]);
		return (127);
	}
	tmp = ctx->envp;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->id, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
